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

UpdateStmt::UpdateStmt(Table *table, const Value *values, int value_amount, const char* field_name, FilterStmt *filter_stmt)
  : table_ (table), values_(values), value_amount_(value_amount), field_name_(field_name), filter_stmt_(filter_stmt)
{}

UpdateStmt::~UpdateStmt()
{
  if (filter_stmt_ != nullptr) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const Updates &update_sql, Stmt *&stmt)
{
  const char *table_name = update_sql.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
             db, table_name);
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
  const Value *value = &update_sql.value;
  char *field_name = update_sql.attribute_name;
  const TableMeta &table_meta = table->table_meta();
  const FieldMeta *field_meta = table_meta.field(field_name);
  const AttrType field_type = field_meta->type();
  const AttrType value_type = value->type;
  if (field_type != value_type) {
    LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
             table_name, field_meta->name(), field_type, value_type);
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  // create filter stmt
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map,
                             update_sql.conditions, update_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, value, 1, field_name, filter_stmt);
  return RC::SUCCESS;
}
