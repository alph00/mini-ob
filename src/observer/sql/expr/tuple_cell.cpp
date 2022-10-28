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
// Created by WangYunlai on 2022/07/05.
//

#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/field.h"
#include "common/log/log.h"
#include "util/comparator.h"
#include "util/util.h"
#include <cmath>
#include <cstdlib>
#include <math.h>

void TupleCell::to_string(std::ostream &os) const
{
  switch (attr_type_) {
    case INTS: {
      os << *(int *)data_;
    } break;
    case DATES: {
      int value = *(int *)data_;
      char buf[16] = {0};
      snprintf(buf,
          sizeof(buf),
          "%04d-%02d-%02d",
          value / 10000,
          (value % 10000) / 100,
          value % 100);  // 注意这里月份和天数，不足两位时需要填充0
      buf[10] = '\0';
      os << buf;
    } break;
    case FLOATS: {
      float v = *(float *)data_;
      os << double2string(v);
    } break;
    case CHARS: {
      for (int i = 0; i < length_; i++) {
        if (data_[i] == '\0') {
          break;
        }
        os << data_[i];
      }
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
}

int TupleCell::compare(const TupleCell &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS:
        return compare_int(this->data_, other.data_);
      case DATES:
        return compare_int(this->data_, other.data_);
      case FLOATS:
        return compare_float(this->data_, other.data_);
      case CHARS:
        return compare_string(this->data_, this->length_, other.data_, other.length_);
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = *(int *)data_;
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {  // to do qfs 不太确定要不要四舍五入？
    float other_data_f = strtof(other.data_, nullptr);
    if (other_data_f - std::floor(other_data_f) < 1e-6) {
      int other_data_i = (int)other_data_f;
      return compare_int(this->data_, &other_data_i);
    } else {
      return compare_float(this->data_, &other_data_f);
    }
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = *(int *)other.data_;
    return compare_float(data_, &other_data);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    float other_data_f = strtof(other.data_, nullptr);
    return compare_float(this->data_, &other_data_f);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {
    float this_data_f = strtof(this->data_, nullptr);
    if (this_data_f - std::floor(this_data_f) < 1e-6) {
      int this_data_i = (int)this_data_f;
      return compare_int(&this_data_i, other.data_);
    } else {
      return compare_float(&this_data_f, other.data_);
    }
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    float this_data_f = strtof(this->data_, nullptr);
    return compare_float(&this_data_f, other.data_);
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}
