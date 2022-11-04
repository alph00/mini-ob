//
// Created by QiuFengShuo on 2022/11/01.
//

#include "join_operator.h"
#include "rc.h"
#include "sql/expr/tuple.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sys/ucontext.h>
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

  return rc;
}

int JoinOperator::tuplesNum()
{
  return table_num;
}
RC JoinOperator::next()
{
  RC rc = RC::SUCCESS;
  if (start) {
    start = false;
    if (left_->next() != RC::RECORD_EOF) {
      Tuple **t = left_->current_tuple();
      if (nullptr == t || nullptr == t[0]) {  // 通过t**,和t[0]*代表
        LOG_WARN("failed to get tuple from operator");
        return RC::INTERNAL;
      }
      // memcpy(tuples_, t, left_->tuplesNum());
      for (size_t i = 0; i < left_->tuplesNum() / (sizeof(Tuple *)); ++i) {
        tuples_[i] = (RowTuple *)t[i];
      }
    } else {
      return RC::RECORD_EOF;
    }
  }
  while (true) {
    RC rc2 = RC::SUCCESS;

    rc2 = right_->next();
    if (rc2 == RC::SUCCESS) {
      Tuple **t0 = right_->current_tuple();
      if (nullptr == t0 || nullptr == t0[0]) {  // 通过t**,和t[0]*代表
        LOG_WARN("failed to get tuple from operator");
        return RC::INTERNAL;
      }
      // memcpy(tuples_ + left_->tuplesNum(), t, right_->tuplesNum());
      for (size_t i = 0; i < right_->tuplesNum() / (sizeof(Tuple *)); ++i) {
        tuples_[left_->tuplesNum() / (sizeof(Tuple *)) + i] = (RowTuple *)t0[i];
      }
      if (do_predicate(tuples_)) {
        return RC::SUCCESS;
      }
    } else if (rc2 == RC::RECORD_EOF) {
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
        // right-next-first
        right_->close();
        right_->open();
        RC rc3 = right_->next();
        if (rc3 != RC::SUCCESS) {
          return rc3;
        }
        Tuple **t1 = right_->current_tuple();
        if (nullptr == t1 || nullptr == t1[0]) {  // 通过t**,和t[0]*代表
          LOG_WARN("failed to get tuple from operator");
          return RC::INTERNAL;
        }

        for (size_t i = 0; i < right_->tuplesNum() / (sizeof(Tuple *)); ++i) {
          tuples_[left_->tuplesNum() / (sizeof(Tuple *)) + i] = (RowTuple *)t1[i];
        }
        if (do_predicate(tuples_)) {
          return RC::SUCCESS;
        }
      } else {
        return RC::RECORD_EOF;
      }
    } else {
      return rc2;
    }
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

bool JoinOperator::do_predicate(RowTuple **tuples_)
{
  if (join_filter_stmt_ == nullptr || join_filter_stmt_->filter_units().empty()) {
    return true;
  }

  for (const FilterUnit *filter_unit : join_filter_stmt_->filter_units()) {
    Expression *left_expr = filter_unit->left();
    Expression *right_expr = filter_unit->right();
    CompOp comp = filter_unit->comp();
    TupleCell left_cell;
    TupleCell right_cell;
    RowTuple *tuplel, *tupler;
    if (left_expr->type() == ExprType::FIELD) {
      size_t id = table_n2id[((FieldExpr *)left_expr)->field().table_name()];
      if (id >= table_num / sizeof(Tuple *)) {
        continue;
      }
      tuplel = tuples_[id];
    }
    if (right_expr->type() == ExprType::FIELD) {
      size_t id = table_n2id[((FieldExpr *)right_expr)->field().table_name()];
      if (id >= table_num / sizeof(Tuple *)) {
        continue;
      }
      tupler = tuples_[id];
    }
    left_expr->get_value(*tuplel, left_cell);
    right_expr->get_value(*tupler, right_cell);

    const int compare = left_cell.compare(right_cell);
    bool filter_result = false;
    switch (comp) {
      case EQUAL_TO: {
        filter_result = (0 == compare);
      } break;
      case LESS_EQUAL: {
        filter_result = (compare <= 0);
      } break;
      case NOT_EQUAL: {
        filter_result = (compare != 0);
      } break;
      case LESS_THAN: {
        filter_result = (compare < 0);
      } break;
      case GREAT_EQUAL: {
        filter_result = (compare >= 0);
      } break;
      case GREAT_THAN: {
        filter_result = (compare > 0);
      } break;
      case LIKE_AS: {
        filter_result = (compare == 0);
      } break;
      case NOT_LIKE: {
        filter_result = (compare != 0);
      } break;
      default: {
        LOG_WARN("invalid compare type: %d", comp);
      } break;
    }
    if (!filter_result) {
      return false;
    }
  }
  return true;
}