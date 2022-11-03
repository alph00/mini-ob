//
// Created by QiuFengShuo on 2022/11/01.
//

#include "join_operator.h"
#include "rc.h"
#include "sql/expr/tuple.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
RC JoinOperator::open()
{
  RC rc = RC::SUCCESS;
  if (left_ == nullptr || right_ == nullptr) {
    LOG_WARN("join operator must has two child");
    return RC::INTERNAL;
  }

  rc = left_->open();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = right_->open();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  table_num = left_->tuplesNum() + right_->tuplesNum();
  tuples_ = (RowTuple **)malloc(table_num);
  // bool first = true;
  // while (RC::SUCCESS == (rc = left_->next())) {
  //   Tuple *tuple = left_->current_tuple();
  //   if (nullptr == tuple) {
  //     rc = RC::INTERNAL;
  //     LOG_WARN("failed to get tuple from operator");
  //     break;
  //   }

  //   RowTuple *tuple_ = new RowTuple;
  //   tuple_->set_record(&(*(RowTuple *)tuple).record());
  //   tuple tuples_.emplace_back(tuple_);
  // }
  rc = left_->next();
  if (rc != RC::RECORD_EOF) {
    Tuple **t = left_->current_tuple();
    if (nullptr == t || nullptr == t[0]) {  // 通过t**,和t[0]*代表
      LOG_WARN("failed to get tuple from operator");
      return RC::INTERNAL;
    }
    // memcpy(tuples_, t, left_->tuplesNum());
    for (size_t i = 0; i < left_->tuplesNum() / (sizeof(Tuple *)); ++i) {
      tuples_[i] = (RowTuple *)t[i];
    }
  }
  return rc;
}
int JoinOperator::tuplesNum()
{
  return table_num;
}
RC JoinOperator::next()
{
  RC rc = RC::SUCCESS;

  // Operator *oper = right_;

  // while (RC::SUCCESS == (rc = oper->next())) {
  //   Tuple *tuple = oper->current_tuple()[0];
  //   if (nullptr == tuple) {
  //     rc = RC::INTERNAL;
  //     LOG_WARN("failed to get tuple from operator");
  //     break;
  //   }

  //   if (do_predicate(static_cast<RowTuple &>(*tuple))) {
  //     return rc;
  //   }
  // }
  while (true) {
    RC rc2 = RC::SUCCESS;
    while (true) {
      rc2 = right_->next();
      if (rc2 != RC::SUCCESS) {
        break;
      }
      Tuple **t = right_->current_tuple();
      if (nullptr == t || nullptr == t[0]) {  // 通过t**,和t[0]*代表
        LOG_WARN("failed to get tuple from operator");
        return RC::INTERNAL;
      }
      // memcpy(tuples_ + left_->tuplesNum(), t, right_->tuplesNum());
      for (size_t i = 0; i < right_->tuplesNum() / (sizeof(Tuple *)); ++i) {
        tuples_[left_->tuplesNum() / (sizeof(Tuple *)) + i] = (RowTuple *)t[i];
      }
      break;
    }
    if (rc2 == RC::RECORD_EOF) {
      right_->close();
      right_->open();
      rc = left_->next();
      if (rc != RC::RECORD_EOF) {
        Tuple **t = left_->current_tuple();
        if (nullptr == t || nullptr == t[0]) {  // 通过t**,和t[0]*代表
          LOG_WARN("failed to get tuple from operator");
          return RC::INTERNAL;
        }
        // memcpy(tuples_, t, left_->tuplesNum());
        for (size_t i = 0; i < left_->tuplesNum() / (sizeof(Tuple *)); ++i) {
          tuples_[i] = (RowTuple *)t[i];
        }
      }
    }
    break;
  }

  return rc;
}
RC JoinOperator::close()
{
  RC rc = RC::SUCCESS;
  rc = left_->close();
  rc = right_->close();
  free(tuples_);
  tuples_ = nullptr;
  return rc;
}
Tuple **JoinOperator::current_tuple()
{
  return (Tuple **)tuples_;
}