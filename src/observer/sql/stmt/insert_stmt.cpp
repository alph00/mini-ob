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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include <cmath>
#include <cstdlib>

InsertStmt::InsertStmt(Table *table, const Values *values, const size_t *value_nums, int values_num)
    : table_(table), values_(values), value_nums_(value_nums), values_num_(values_num)
{}

const Value * InsertStmt::values(size_t idx) const
{
  if (idx > values_num_) {
    LOG_WARN("invalid index %d to values", idx);
    return nullptr;
  }
  return values_[idx];
}

size_t InsertStmt::value_amount(size_t idx) const
{
  if (idx > values_num_) {
    LOG_WARN("invalid index %d to value_nums", idx);
    return 0;
  }
  return value_nums_[idx];
}

RC InsertStmt::create(Db *db, const Inserts &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name;

  if (nullptr == db || nullptr == table_name || inserts.values_num <= 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, values_num=%d", db, table_name, inserts.values_num);
    return RC::INVALID_ARGUMENT;
  }
  for (int i = 0; i < inserts.values_num; i++) {
    if (inserts.value_nums[i] <= 0) {
      LOG_WARN("invalid argument. db=%p, table_name=%p, values_num=%d, value_num=%d", db, table_name, i, inserts.values_num);
      return RC::INVALID_ARGUMENT;
    }
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  const size_t values_num = inserts.values_num;
  const Values *values_array = inserts.values_array;
  const size_t *value_nums = inserts.value_nums;
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();
  for (size_t i = 0; i < values_num; i++) {
    if (field_num != value_nums[i]) {
      LOG_WARN("schema mismatch in %dth values. value num=%d, field num in schema=%d", i, value_nums[i], field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  for (size_t i = 0; i < values_num; i++) {
    const size_t value_num = value_nums[i];
    const Value *values = values_array[i];
    for (size_t j = 0; j < value_num; j++) {
      const FieldMeta *field_meta = table_meta.field(j + sys_field_num);
      const AttrType field_type = field_meta->type();
      const AttrType value_type = values[j].type;
      if (field_type != value_type) {  // TODO try to convert the value type to field type
        if (field_type == DATES || value_type == DATES) {
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
                   table_name,
                   field_meta->name(),
                   field_type,
                   value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        } else if (field_type == INTS && value_type == FLOATS) {
          float data_f = *(float *)values[j].data;
          int data_i = std::round(data_f);
          memcpy(values[j].data, &data_i, sizeof(data_i));
          LOG_WARN("qfs data:%d", *(int *)values[j].data);
        } else if (field_type == INTS && value_type == CHARS) {  // to do qfs 不太确定要不要四舍五入？
          int data_i = round(strtof((char *)values[j].data, nullptr));
          memcpy(values[j].data, &data_i, sizeof(data_i));
        } else if (field_type == FLOATS && value_type == INTS) {
          int data_i = *(int *)values[j].data;
          float data_f = data_i * 1.0;
          memcpy(values[j].data, &data_f, sizeof(data_f));
        } else if (field_type == FLOATS && value_type == CHARS) {
          float data_f = strtof((char *)values[j].data, nullptr);
          memcpy(values[j].data, &data_f, sizeof(data_f));
        } else if (field_type == CHARS && value_type == INTS) {
          int data_i = *(int *)values[j].data;
          sprintf((char *)values[j].data, "%d", data_i);
        } else if (field_type == CHARS && value_type == FLOATS) {  // to do qfs 可能会有数太大用e表示的问题？
          float data_f = *(float *)values[j].data;
          sprintf((char *)values[j].data, "%g", data_f);
        } else {
          LOG_WARN("other type cast!");
        }
      }
    }
  }

  // everything alright
  stmt = new InsertStmt(table, values_array, value_nums, values_num);
  return RC::SUCCESS;
}
