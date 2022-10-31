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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/project_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

RC ProjectOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("project operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectOperator::next()
{
  return children_[0]->next();
}

RC ProjectOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
Tuple *ProjectOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}

void ProjectOperator::add_projection(
    const Table *table, const FieldMeta *field_meta, const bool isAggrefunc, const Aggrefunc *func)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(new FieldExpr(table, field_meta));
  if (isAggrefunc) {
    char *header = (char *)malloc(MAX_ATTR_NAME + 10);
    switch (func->type) {
      case COUNTS: {
        strcpy(header, "count(");
      } break;
      case AVGS: {
        strcpy(header, "avg(");
      } break;
      case SUMS: {
        strcpy(header, "sum(");
      } break;
      case MAXS: {
        strcpy(header, "max(");
      } break;
      case MINS: {
        strcpy(header, "min(");
      } break;
      default: {
      }
    }
    if (field_meta == nullptr) {
      if (func->num >= 0) {
        char num[10];
        sprintf(num, "%d", func->num);
        strcat(header, num);
      } else {
        strcat(header, "*");
      }
    } else {
      strcat(header, field_meta->name());
    }
    strcat(header, ")");
    spec->set_alias(header);
  } else {
    spec->set_alias(field_meta->name());
  }
  tuple_.add_cell_spec(spec);
}

RC ProjectOperator::tuple_cell_spec_at(int index, const TupleCellSpec *&spec) const
{
  return tuple_.cell_spec_at(index, spec);
}