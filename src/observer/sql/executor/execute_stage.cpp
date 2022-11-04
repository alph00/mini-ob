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
// Created by Meiyi & Longda on 2021/4/13.
//

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/lang/defer.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/expr/tuple.h"
#include "sql/operator/join_operator.h"
#include "sql/operator/operator.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/update_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/table.h"
#include "storage/common/field.h"
#include "storage/index/index.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"
#include "util/util.h"

using namespace common;

// RC create_selection_executor(
//    Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag)
{}

//! Destructor
ExecuteStage::~ExecuteStage()
{}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag)
{
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties()
{
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize()
{
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup()
{
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event)
{
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context)
{
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event)
{
  SQLStageEvent *sql_event = static_cast<SQLStageEvent *>(event);
  SessionEvent *session_event = sql_event->session_event();
  Stmt *stmt = sql_event->stmt();
  Session *session = session_event->session();
  Query *sql = sql_event->query();

  if (stmt != nullptr) {
    switch (stmt->type()) {
      case StmtType::SELECT: {
        do_select(sql_event);
      } break;
      case StmtType::INSERT: {
        do_insert(sql_event);
      } break;
      case StmtType::UPDATE: {
        do_update(sql_event);
      } break;
      case StmtType::DELETE: {
        do_delete(sql_event);
      } break;
      default: {
        LOG_WARN("should not happen. please implenment");
      } break;
    }
  } else {
    switch (sql->flag) {
      case SCF_HELP: {
        do_help(sql_event);
      } break;
      case SCF_CREATE_TABLE: {
        do_create_table(sql_event);
      } break;
      case SCF_CREATE_INDEX: {
        do_create_index(sql_event);
      } break;
      case SCF_SHOW_TABLES: {
        do_show_tables(sql_event);
      } break;
      case SCF_SHOW_INDEX: {
        do_show_index(sql_event);
      } break;
      case SCF_DESC_TABLE: {
        do_desc_table(sql_event);
      } break;

      case SCF_DROP_TABLE: {
        do_drop_table(sql_event);
      } break;
      case SCF_DROP_INDEX:
      case SCF_LOAD_DATA: {
        default_storage_stage_->handle_event(event);
      } break;
      case SCF_SYNC: {
        /*
        RC rc = DefaultHandler::get_default().sync();
        session_event->set_response(strrc(rc));
        */
      } break;
      case SCF_BEGIN: {
        do_begin(sql_event);
        /*
        session_event->set_response("SUCCESS\n");
        */
      } break;
      case SCF_COMMIT: {
        do_commit(sql_event);
        /*
        Trx *trx = session->current_trx();
        RC rc = trx->commit();
        session->set_trx_multi_operation_mode(false);
        session_event->set_response(strrc(rc));
        */
      } break;
      case SCF_CLOG_SYNC: {
        do_clog_sync(sql_event);
      }
      case SCF_ROLLBACK: {
        Trx *trx = session_event->get_client()->session->current_trx();
        RC rc = trx->rollback();
        session->set_trx_multi_operation_mode(false);
        session_event->set_response(strrc(rc));
      } break;
      case SCF_EXIT: {
        // do nothing
        const char *response = "Unsupported\n";
        session_event->set_response(response);
      } break;
      default: {
        LOG_ERROR("Unsupported command=%d\n", sql->flag);
      }
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right)
{
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

void print_tuple_header(std::ostream &os, const ProjectOperator &oper, int num = 1)
{
  bool enter = false;
  bool start = false;
  for (int j = 0; j < num; ++j) {
    const int cell_num = oper.tuple_cell_num(j);
    const TupleCellSpec *cell_spec = nullptr;
    for (int i = 0; i < cell_num; i++) {
      oper.tuple_cell_spec_at(i, cell_spec, j);
      if (start) {
        os << " | ";
      } else {
        start = true;
      }

      if (cell_spec->alias()) {
        os << cell_spec->alias();
      }
    }

    if (cell_num > 0) {
      enter = true;
    }
  }
  if (enter) {
    os << '\n';
  }
}
void tuple_to_string(std::ostream &os, Tuple **tuples_, int num)
{
  TupleCell cell;
  RC rc = RC::SUCCESS;
  bool first_field = true;
  Tuple *tuple;
  for (int j = 0; j < num; ++j) {
    tuple = tuples_[j];
    for (int i = 0; i < tuple->cell_num(); i++) {
      rc = tuple->cell_at(i, cell);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to fetch field of cell. index=%d, rc=%s", i, strrc(rc));
        break;
      }

      if (!first_field) {
        os << " | ";
      } else {
        first_field = false;
      }
      cell.to_string(os);
    }
  }
}

IndexScanOperator *try_to_create_index_scan_operator(FilterStmt *filter_stmt)
{
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  if (filter_units.empty()) {
    return nullptr;
  }

  // 在所有过滤条件中，找到字段与值做比较的条件，然后判断字段是否可以使用索引
  // 如果是多列索引，这里的处理需要更复杂。
  // 这里的查找规则是比较简单的，就是尽量找到使用相等比较的索引
  // 如果没有就找范围比较的，但是直接排除不等比较的索引查询. (你知道为什么?)
  const FilterUnit *better_filter = nullptr;
  for (const FilterUnit *filter_unit : filter_units) {
    if (filter_unit->comp() == NOT_EQUAL) {
      continue;
    }

    Expression *left = filter_unit->left();
    Expression *right = filter_unit->right();
    if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
    } else if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
      std::swap(left, right);
    } else {
      continue;
    }
    FieldExpr &left_field_expr = *(FieldExpr *)left;
    const Field &field = left_field_expr.field();
    const Table *table = field.table();
    Index *index = table->find_index_by_field(field.field_name());
    if (index != nullptr) {
      if (better_filter == nullptr) {
        better_filter = filter_unit;
      } else if (filter_unit->comp() == EQUAL_TO) {
        better_filter = filter_unit;
        break;
      }
    }
  }

  if (better_filter == nullptr) {
    return nullptr;
  }

  Expression *left = better_filter->left();
  Expression *right = better_filter->right();
  CompOp comp = better_filter->comp();
  if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
    std::swap(left, right);
    switch (comp) {
      case EQUAL_TO: {
        comp = EQUAL_TO;
      } break;
      case LESS_EQUAL: {
        comp = GREAT_THAN;
      } break;
      case NOT_EQUAL: {
        comp = NOT_EQUAL;
      } break;
      case LESS_THAN: {
        comp = GREAT_EQUAL;
      } break;
      case GREAT_EQUAL: {
        comp = LESS_THAN;
      } break;
      case GREAT_THAN: {
        comp = LESS_EQUAL;
      } break;
      default: {
        LOG_WARN("should not happen");
      }
    }
  }

  FieldExpr &left_field_expr = *(FieldExpr *)left;
  const Field &field = left_field_expr.field();
  const Table *table = field.table();
  Index *index = table->find_index_by_field(field.field_name());
  assert(index != nullptr);

  ValueExpr &right_value_expr = *(ValueExpr *)right;
  TupleCell value;
  right_value_expr.get_tuple_cell(value);

  const TupleCell *left_cell = nullptr;
  const TupleCell *right_cell = nullptr;
  bool left_inclusive = false;
  bool right_inclusive = false;

  switch (comp) {  // 这些是区间边界
    case EQUAL_TO: {
      left_cell = &value;
      right_cell = &value;
      left_inclusive = true;
      right_inclusive = true;
    } break;

    case LESS_EQUAL: {
      left_cell = nullptr;
      left_inclusive = false;
      right_cell = &value;
      right_inclusive = true;
    } break;

    case LESS_THAN: {
      left_cell = nullptr;
      left_inclusive = false;
      right_cell = &value;
      right_inclusive = false;
    } break;

    case GREAT_EQUAL: {
      left_cell = &value;
      left_inclusive = true;
      right_cell = nullptr;
      right_inclusive = false;
    } break;

    case GREAT_THAN: {
      left_cell = &value;
      left_inclusive = false;
      right_cell = nullptr;
      right_inclusive = false;
    } break;

    default: {
      LOG_WARN("should not happen. comp=%d", comp);
    } break;
  }

  IndexScanOperator *oper = new IndexScanOperator(table, index, left_cell, left_inclusive, right_cell, right_inclusive);

  LOG_INFO("use index for scan: %s in table %s", index->index_meta().name(), table->name());
  return oper;
}
void print_Aggrefunc_header(std::ostream &os, const ProjectOperator &oper, size_t num)
{
  const TupleCellSpec *cell_spec = nullptr;
  for (size_t i = 0; i < num; i++) {
    oper.tuple_cell_spec_at(i, cell_spec);
    if (i != 0) {
      os << " | ";
    }

    if (cell_spec->alias()) {
      os << cell_spec->alias();
    }
  }

  if (num > 0) {
    os << '\n';
  }
}
void AggrefuncPrint(
    std::ostream &os, const std::vector<Field> &query_fields, AggrefuncPara *para, std::vector<Value *> *values)
{
  bool first_field = true;
  // when values isn't null, query_field.size must be one
  assert(values == nullptr || ((values != nullptr) && query_fields.size() == 1));
  Value *value = (Value *)malloc(sizeof(Value));

  for (size_t i = 0; i < query_fields.size(); ++i) {
    if (!first_field) {
      os << " | ";
    } else {
      first_field = false;
    }
    switch (query_fields[i].aggrefunc()->type) {
      case COUNTS: {
        if (values == nullptr) {
          os << para[i].count;
        } else {
          value_init_integer(value, para[i].count);
        }
      } break;
      case AVGS: {
        switch (query_fields[i].attr_type()) {
          case CHARS: {
            if (values == nullptr) {
              os << double2string(para[i].sum / para[i].count);
            } else {
              value_init_string(value, double2string(para[i].sum / para[i].count).c_str());
            }
          } break;
          case FLOATS: {
            if (values == nullptr) {
              os << double2string(para[i].sum / para[i].count);
            } else {
              value_init_float(value, para[i].sum / para[i].count);
            }
          } break;
          case INTS: {
            if (values == nullptr) {
              os << double2string(para[i].sum / para[i].count);
            } else {
              value_init_integer(value, para[i].sum / para[i].count);
            }
          } break;
          default: {
            free(value);
            value = nullptr;
          } break;
        }
      } break;
      case MAXS: {
        switch (query_fields[i].attr_type()) {
          case INTS: {
            if (values == nullptr) {
              os << para[i].max_i;
            } else {
              value_init_integer(value, para[i].max_i);
            }
          } break;
          case FLOATS: {
            if (values == nullptr) {
              os << double2string(para[i].max_f);
            } else {
              value_init_integer(value, para[i].max_f);
            }
          } break;
          case CHARS: {  // to do qfs ?
            if (values == nullptr) {
              os << para[i].max_c;
            } else {
              value_init_string(value, para[i].max_c);
            }
          } break;
          case DATES: {
            int data = para[i].max_i;
            if (values == nullptr) {
              char buf[16] = {0};
              snprintf(buf,
                  sizeof(buf),
                  "%04d-%02d-%02d",
                  data / 10000,
                  (data % 10000) / 100,
                  data % 100);  // 注意这里月份和天数，不足两位时需要填充0
              buf[10] = '\0';
              os << buf;
            } else {
              value_init_integer(value, data);
            }
          } break;
          default: {
            free(value);
            value = nullptr;
          } break;
        }
      } break;
      case MINS: {
        switch (query_fields[i].attr_type()) {
          case INTS: {
            if (values == nullptr) {
              os << para[i].min_i;
            } else {
              value_init_integer(value, para[i].min_i);
            }
          } break;
          case FLOATS: {
            if (values == nullptr) {
              os << double2string(para[i].min_f);
            } else {
              value_init_float(value, para[i].min_f);
            }
          } break;
          case CHARS: {
            if (values == nullptr) {
              os << para[i].min_c;
            } else {
              value_init_string(value, para[i].min_c);
            }
          } break;
          case DATES: {
            int data = para[i].min_i;
            if (values == nullptr) {
              char buf[16] = {0};
              snprintf(buf,
                  sizeof(buf),
                  "%04d-%02d-%02d",
                  data / 10000,
                  (data % 10000) / 100,
                  data % 100);  // 注意这里月份和天数，不足两位时需要填充0
              buf[10] = '\0';
              os << buf;
            } else {
              value_init_integer(value, data);
            }
          } break;
          default: {
            free(value);
            value = nullptr;
          } break;
        }
      } break;
      case SUMS: {
        switch (query_fields[i].attr_type()) {
          case FLOATS: {
            if (values == nullptr) {
              os << double2string(para[i].sum);
            } else {
              value_init_float(value, para[i].sum);
            }
          } break;
          case CHARS: {  //?
            if (values == nullptr) {
              os << double2string(para[i].sum);
            } else {
              value_init_string(value, double2string(para[i].sum).c_str());
            }
          } break;
          case INTS: {
            if (values == nullptr) {
              os << (int)para[i].sum;
            } else {
              value_init_integer(value, (int)para[i].sum);
            }
          } break;
          default: {
            free(value);
            value = nullptr;
          } break;
        }
      } break;
      default: {
        free(value);
        value = nullptr;
      } break;
    }
  }

  if (value != nullptr && values != nullptr) {
    values->push_back(value);
  } else {
    os << std::endl;
  }
}

RC processAggrefunc(const std::vector<Field> &query_fields, AggrefuncPara *para, Tuple *tuple)
{
  RC rc = RC::SUCCESS;
  for (size_t i = 0; i < query_fields.size(); ++i) {
    const Aggrefunc *func = query_fields[i].aggrefunc();
    switch (func->type) {
      case COUNTS: {
        if (query_fields[i].meta() == nullptr) {
          if (func->num >= 0) {  // count(1)
            para[i].count += func->num;
          } else {  // count(*)
            para[i].count += 1;
          }
        } else {
          // 目前不考虑NULL
          para[i].count += 1;
        }
      } break;
      case AVGS: {
        TupleCell cell;
        rc = tuple->cell_at(i, cell);
        para[i].count += 1;
        const char *data = cell.data();
        switch (cell.attr_type()) {
          case FLOATS: {
            para[i].sum += *(float *)data;
          } break;
          case INTS:
          case DATES: {
            para[i].sum += *(int *)data;
          } break;
          case CHARS: {
            char *data_c = strdup(data);
            float data_f = strtof(data_c, nullptr);
            para[i].sum += data_f;
            free(data_c);
          } break;
          default: {
          } break;
        }
      } break;
      case MAXS: {
        TupleCell cell;
        rc = tuple->cell_at(i, cell);
        const char *data = cell.data();
        switch (cell.attr_type()) {
          case FLOATS: {
            para[i].max_f = std::max(para[i].max_f, *(float *)data);
          }
          case INTS:
          case DATES: {
            para[i].max_i = std::max(para[i].max_i, *(int *)data);
          } break;
          case CHARS: {
            if (strcmp(para[i].max_c, data) < 0) {
              strcpy(para[i].max_c, data);
            }
          } break;
          default: {
          } break;
        }
      } break;
      case MINS: {
        TupleCell cell;
        rc = tuple->cell_at(i, cell);
        const char *data = cell.data();
        switch (cell.attr_type()) {
          case FLOATS: {
            para[i].min_f = std::min(para[i].min_f, *(float *)data);
          }
          case INTS:
          case DATES: {
            para[i].min_i = std::min(para[i].min_i, *(int *)data);
          } break;
          case CHARS: {
            if (strcmp(para[i].min_c, data) > 0) {
              strcpy(para[i].min_c, data);
            }
          } break;
          default: {
          } break;
        }
      } break;
      case SUMS: {
        TupleCell cell;
        rc = tuple->cell_at(i, cell);
        const char *data = cell.data();
        switch (cell.attr_type()) {
          case FLOATS: {
            para[i].sum += *(float *)data;
          } break;
          case INTS:
          case DATES: {
            para[i].sum += *(int *)data;
          } break;
          case CHARS: {
            char *data_c = strdup(data);
            float data_f = strtof(data_c, nullptr);
            para[i].sum += data_f;
            free(data_c);
          } break;
          default: {
          } break;
        }
      } break;
    }
  }
  return rc;
}

RC ExecuteStage::do_select(SQLStageEvent *sql_event, std::vector<Value *> *values)
{
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  RC rc = RC::SUCCESS;
  for (size_t i = 0; i < select_stmt->tables().size(); ++i) {
    std::string str = select_stmt->tables()[i]->table_meta().name();
    table_n2id[str] = select_stmt->tables().size() - i - 1;
  }

  // sub selection should return rows with one field
  if (values != nullptr && select_stmt->query_fields().size() != 1) {
    return RC::INTERNAL;
  }

  // DEFER([&]() { delete[] scan_oper; });
  Operator *scan_oper[select_stmt->tables().size()];
  Operator *join_oper[select_stmt->tables().size()];
  PredicateOperator pred_oper(select_stmt->filter_stmt());
  if (select_stmt->tables().size() > 1) {
    // 多表查询目前不考虑索引
    for (size_t i = 0; i < select_stmt->tables().size(); ++i) {
      scan_oper[i] = new TableScanOperator(select_stmt->tables()[select_stmt->tables().size() - 1 - i]);
    }
    join_oper[0] = new JoinOperator(scan_oper[0], scan_oper[1], select_stmt->join_filter_stmt());
    for (size_t i = 1; i < select_stmt->tables().size() - 1; ++i) {
      join_oper[i] = new JoinOperator(join_oper[i - 1], scan_oper[i + 1], select_stmt->join_filter_stmt());
    }
    pred_oper.add_child(join_oper[select_stmt->tables().size() - 2]);
  } else {  // 单表
    scan_oper[0] = try_to_create_index_scan_operator(select_stmt->filter_stmt());
    if (nullptr == scan_oper[0]) {
      scan_oper[0] = new TableScanOperator(select_stmt->tables()[0]);
    }
    pred_oper.add_child(scan_oper[0]);
  }
  ProjectOperator project_oper;
  project_oper.add_child(&pred_oper);
  rc = project_oper.open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open operator");
    return rc;
  }
  for (const Field &field : select_stmt->query_fields()) {
    project_oper.add_projection(
        field.table(), field.meta(), field.isAggrefunc(), field.aggrefunc(), table_n2id[field.table()->name()]);
  }

  // 目前认为普通查询和聚合函数不能同时存在
  // 目前聚合函数不能多表查询
  // 先不考虑sum(2)这种
  std::stringstream ss;
  if (select_stmt->query_fields()[0].isAggrefunc() == true) {  // to do qfs
    print_Aggrefunc_header(ss, project_oper, select_stmt->query_fields().size());
    AggrefuncPara para[select_stmt->query_fields().size()];
    while ((rc = project_oper.next()) == RC::SUCCESS) {
      Tuple *tuple = project_oper.current_tuple()[0];
      if (nullptr == tuple) {
        rc = RC::INTERNAL;
        LOG_WARN("failed to get current record. rc=%s", strrc(rc));
        break;
      }
      processAggrefunc(select_stmt->query_fields(), para, tuple);
    }
    AggrefuncPrint(ss, select_stmt->query_fields(), para, values);
  } else {
    print_tuple_header(ss, project_oper, select_stmt->tables().size());
    while ((rc = project_oper.next()) == RC::SUCCESS) {
      // get current record
      // write to response
      Tuple **tuple = project_oper.current_tuple();
      if (nullptr == tuple || nullptr == tuple[0]) {
        rc = RC::INTERNAL;
        LOG_WARN("failed to get current record. rc=%s", strrc(rc));
        break;
      }

      if (values == nullptr) {
        tuple_to_string(ss, tuple, project_oper.tuplesNum() / sizeof(Tuple *));
        ss << std::endl;
      } else {
        TupleCell cell;
        rc = (*tuple)->cell_at(0, cell);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to fetch field of cell. index=%d, rc=%s", 0, strrc(rc));
          break;
        }

        Value *value = (Value *)malloc(sizeof(Value));
        rc = cell.get_value(value);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to transfer field to value, index=%d, rc=%s", 0, strrc(rc));
          return rc;
        }
        values->push_back(value);
      }
    }
  }

  if (rc != RC::RECORD_EOF) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    project_oper.close();
  } else {
    rc = project_oper.close();
  }

  if (values == nullptr) {
    session_event->set_response(ss.str());
  }

  // 资源释放，替代之前的defer
  for (size_t i = 0; i < select_stmt->tables().size(); ++i) {
    delete scan_oper[i];
    if (i != select_stmt->tables().size() - 1) {
      delete join_oper[i];
    }
  }
  table_n2id.clear();
  //
  return rc;
}

RC ExecuteStage::do_help(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  const char *response = "show tables;\n"
                         "desc `table name`;\n"
                         "create table `table name` (`column name` `column type`, ...);\n"
                         "create index `index name` on `table` (`column`);\n"
                         "insert into `table` values(`value1`,`value2`);\n"
                         "update `table` set column=value [where `column`=`value`];\n"
                         "delete from `table` [where `column`=`value`];\n"
                         "select [ * | `columns` ] from `table`;\n";
  session_event->set_response(response);
  return RC::SUCCESS;
}
RC ExecuteStage::do_drop_table(SQLStageEvent *sql_event)
{
  const DropTable &drop_table = sql_event->query()->sstr.drop_table;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  RC rc = db->drop_table(drop_table.relation_name);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}
RC ExecuteStage::do_create_table(SQLStageEvent *sql_event)
{
  const CreateTable &create_table = sql_event->query()->sstr.create_table;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  RC rc = db->create_table(create_table.relation_name, create_table.attribute_count, create_table.attributes);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}
RC ExecuteStage::do_create_index(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  const CreateIndex &create_index = sql_event->query()->sstr.create_index;
  Table *table = db->find_table(create_index.relation_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  RC rc = table->create_index(nullptr, create_index.index_name, create_index.attribute_name);
  sql_event->session_event()->set_response(rc == RC::SUCCESS ? "SUCCESS\n" : "FAILURE\n");
  return rc;
}
RC ExecuteStage::do_show_index(SQLStageEvent *sql_event)
{
  const ShowIndex &show_index = sql_event->query()->sstr.show_index;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();

  Table *table = db->find_table(show_index.relation_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::string result = "";
  RC rc = table->show_index_info(result);
  if (rc != RC::SUCCESS)
    return rc;

  std::stringstream ss;
  ss << "TABLE | NON_UNIQUE | KEY_NAME | SEQ_IN_INDEX | COLUMN_NAME" << std::endl;
  ss << result;
  session_event->set_response(ss.str().c_str());
  return RC::SUCCESS;
}
RC ExecuteStage::do_show_tables(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  std::vector<std::string> all_tables;
  db->all_tables(all_tables);
  if (all_tables.empty()) {
    session_event->set_response("No table\n");
  } else {
    std::stringstream ss;
    for (const auto &table : all_tables) {
      ss << table << std::endl;
    }
    session_event->set_response(ss.str().c_str());
  }
  return RC::SUCCESS;
}

RC ExecuteStage::do_desc_table(SQLStageEvent *sql_event)
{
  Query *query = sql_event->query();
  Db *db = sql_event->session_event()->session()->get_current_db();
  const char *table_name = query->sstr.desc_table.relation_name;
  Table *table = db->find_table(table_name);
  std::stringstream ss;
  if (table != nullptr) {
    table->table_meta().desc(ss);
  } else {
    ss << "No such table: " << table_name << std::endl;
  }
  sql_event->session_event()->set_response(ss.str().c_str());
  return RC::SUCCESS;
}

RC ExecuteStage::do_insert(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();
  RC rc = RC::SUCCESS;

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  InsertStmt *insert_stmt = (InsertStmt *)stmt;
  Table *table = insert_stmt->table();

  rc = table->insert_record(trx, insert_stmt->values_num(), insert_stmt->values_array(), insert_stmt->value_nums());
  if (rc == RC::SUCCESS) {
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    } else {
      session_event->set_response("SUCCESS\n");
    }
  } else {
    session_event->set_response("FAILURE\n");
  }

  return rc;
}

RC ExecuteStage::do_delete(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  DeleteStmt *delete_stmt = (DeleteStmt *)stmt;
  TableScanOperator scan_oper(delete_stmt->table());
  PredicateOperator pred_oper(delete_stmt->filter_stmt());
  pred_oper.add_child(&scan_oper);
  DeleteOperator delete_oper(delete_stmt, trx);
  delete_oper.add_child(&pred_oper);

  RC rc = delete_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    }
  }
  return rc;
}

RC ExecuteStage::do_update(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Trx *trx = session->current_trx();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  UpdateStmt *update_stmt = (UpdateStmt *)stmt;
  RC rc = RC::SUCCESS;

  // execute sub query
  for (size_t i = 0; i < update_stmt->field_num(); i++) {
    if (update_stmt->value(i)->type == SELECTS) {
      auto actual_values = new std::vector<Value *>();
      rc = get_value(sql_event, (SelectStmt *)update_stmt->value(i)->data, actual_values);
      if (rc != RC::SUCCESS) {
        LOG_WARN("fail to get value of sub select_stmt");
        session_event->set_response("FAILURE\n");
        return rc;
      }
      free(update_stmt->value(i)->data);
      update_stmt->set_value(i, actual_values->at(0)->type, actual_values->at(0)->data);
      free(actual_values);
    }
  }

  TableScanOperator scan_oper(update_stmt->table());
  PredicateOperator pred_oper(update_stmt->filter_stmt());
  pred_oper.add_child(&scan_oper);
  UpdateOperator update_oper(update_stmt, trx);
  update_oper.add_child(&pred_oper);

  rc = update_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}

RC ExecuteStage::do_begin(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(true);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_BEGIN, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}

RC ExecuteStage::do_commit(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(false);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  trx->next_current_id();

  return rc;
}

RC ExecuteStage::do_clog_sync(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  CLogManager *clog_manager = db->get_clog_manager();

  rc = clog_manager->clog_sync();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}

RC ExecuteStage::get_value(SQLStageEvent *sql_event, SelectStmt *select_stmt, std::vector<Value *> *values)
{
  RC rc = RC::SUCCESS;

  UpdateStmt *stmt = (UpdateStmt *)sql_event->stmt();
  sql_event->set_stmt(select_stmt);
  do_select(sql_event, values);
  sql_event->set_stmt(stmt);
  if (values->size() != 1) {
    LOG_WARN("values returned by sub selection show be 1");
    return RC::INTERNAL;
  }
  return RC::SUCCESS;
  //  if (select_stmt->tables().size() != 1) {
  //    LOG_WARN("select more than 1 tables is not supported");
  //    rc = RC::UNIMPLENMENT;
  //    return rc;
  //  }
  //  if (select_stmt->query_fields().size() != 1) {
  //    LOG_WARN("select more than 1 field is not allowed");
  //    rc = RC::INVALID_ARGUMENT;
  //    return rc;
  //  }
  //
  //  Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
  //  if (nullptr == scan_oper) {
  //    scan_oper = new TableScanOperator(select_stmt->tables()[0]);
  //  }
  //
  //  DEFER([&]() { delete scan_oper; });
  //
  //  PredicateOperator pred_oper(select_stmt->filter_stmt());
  //  pred_oper.add_child(scan_oper);
  //  ProjectOperator project_oper;
  //  project_oper.add_child(&pred_oper);
  //  for (const Field &field : select_stmt->query_fields()) {
  //    project_oper.add_projection(field.table(), field.meta());
  //  }
  //  rc = project_oper.open();
  //  if (rc != RC::SUCCESS) {
  //    LOG_WARN("failed to open operator");
  //    return rc;
  //  }
  //
  //
  //  size_t record_num = 0;
  //  while ((rc = project_oper.next()) == RC::SUCCESS) {
  //    if (++record_num > 1) {
  //      break;
  //    }
  //    Tuple *tuple = project_oper.current_tuple();
  //    TupleCell cell;
  //    rc = tuple->cell_at(0, cell);
  //    if (rc != RC::SUCCESS) {
  //      LOG_WARN("failed to fetch field of cell. index=%d, rc=%s", 0, strrc(rc));
  //      break;
  //    }
  //
  //    rc = cell.get_value(value);
  //    if (rc != RC::SUCCESS) {
  //      LOG_WARN("failed to transfer field to value, index=%d, rc=%s", 0, strrc(rc));
  //      return rc;
  //    }
  //  }
  //
  //  if (rc != RC::RECORD_EOF) {
  //    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
  //    project_oper.close();
  //  } else {
  //    rc = project_oper.close();
  //  }
  //
  //  if (record_num == 0) {
  //    rc = RC::INTERNAL;
  //  }
  return rc;
}