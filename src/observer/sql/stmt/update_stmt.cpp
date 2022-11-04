/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "common/log/log.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

UpdateStmt::UpdateStmt(
    Table *table, const Value values[], int value_amount, const char *const field_name[], FilterStmt *filter_stmt)
    : table_(table), values_(values), value_amount_(value_amount), field_name_(field_name), filter_stmt_(filter_stmt)
{}

UpdateStmt::~UpdateStmt()
{
  if (filter_stmt_ != nullptr) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

const char *UpdateStmt::field_name(size_t idx) const
{
  if (idx >= value_amount_) {
    LOG_WARN("invalid index %d to fields", idx);
    return nullptr;
  }

  return field_name_[idx];
}

const Value *UpdateStmt::value(size_t idx) const
{
  if (idx >= value_amount_) {
    LOG_WARN("invalid index %d to values", idx);
    return nullptr;
  }

  return values_ + idx;
}

void UpdateStmt::set_value(size_t idx, AttrType type, void *data)
{
  if (idx >= value_amount_) {
    LOG_WARN("invalid index %d to values", idx);
    return;
  }
  Value *temp = const_cast<Value *>(values_ + idx);
  temp->type = type;
  temp->data = data;
}

RC UpdateStmt::create(Db *db, const Updates &update_sql, Stmt *&stmt)
{
  const char *table_name = update_sql.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // only update one filed, no need to check fields number
  // ...

  // check fields type
  for (size_t i = 0; i < update_sql.value_num; i++) {
    Value *value = const_cast<Value *>(update_sql.values + i);
    char *field_name = update_sql.attribute_name[i];
    const TableMeta &table_meta = table->table_meta();
    const FieldMeta *field_meta = table_meta.field(field_name);
    if (field_meta == nullptr) {
      LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // const AttrType field_type = field_meta->type();
    const AttrType value_type = value->type;
    if (value_type == SELECTS) {
      Stmt *stmt = nullptr;
      RC rc = Stmt::create_stmt(db, *(Query *)value->data, stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create stmt. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      //        query_destroy((Query*)value->data);
      value->data = stmt;
      LOG_DEBUG("succeed to process sub select query");
    }
  }

  // create attribute names
  char **attr_names = (char **)malloc(sizeof(char *) * update_sql.value_num);
  for (size_t i = 0; i < update_sql.value_num; i++) {
    attr_names[i] = strdup(update_sql.attribute_name[i]);
  }

  // create filter stmt
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update_sql.conditions, update_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, update_sql.values, update_sql.value_num, attr_names, filter_stmt);
  return RC::SUCCESS;
}
