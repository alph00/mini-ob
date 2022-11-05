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

#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/operator.h"
#include "rc.h"
#include <vector>

class ProjectOperator : public Operator {
public:
  ProjectOperator()
  {}

  virtual ~ProjectOperator() = default;

  void add_projection(
      const Table *table, const FieldMeta *field, const bool isAggrefunc, const Aggrefunc *func, int i = 0);

  RC open() override;
  RC next() override;
  RC close() override;

  int tuple_cell_num(int i = 0) const
  {
    return ((ProjectTuple *)tuples_[i])->cell_num();
  }

  RC tuple_cell_spec_at(int index, const TupleCellSpec *&spec, int i = 0) const;

  Tuple **current_tuple() override;
  int tuplesNum() override;

private:
  // ProjectTuple *tuples_ = nullptr;
  Tuple **tuples_ = nullptr;
  // char *alias = nullptr;
  std::vector<char *> alias;
  int table_sum = 0;
};
