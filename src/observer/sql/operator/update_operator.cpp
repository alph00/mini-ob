//
// Created by hsy on 22-10-26.
//

#include "common/log/log.h"
#include "sql/operator/update_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"

RC UpdateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("update operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  Table *table = update_stmt_->table();
  const FieldMeta *fields[MAX_NUM];
  const size_t field_num = update_stmt_->field_num();
  size_t copy_lens[MAX_NUM];
  for (size_t i = 0; i < field_num; i++) {
    fields[i] = table->table_meta().field(update_stmt_->field_name(i));
    const AttrType field_type = fields[i]->type();
    const AttrType value_type = update_stmt_->value(i)->type;
    const Value *value = update_stmt_->value(i);
    if (field_type != value_type) {  // TODO try to convert the value type to field type
      if (field_type == DATES || value_type == DATES) {
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            table->table_meta().name(),
            fields[i]->name(),
            field_type,
            value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      } else if (field_type == INTS && value_type == FLOATS) {
        float data_f = *(float *)value->data;
        int data_i = std::round(data_f);
        memcpy(value->data, &data_i, sizeof(data_i));
        LOG_WARN("qfs data:%d", *(int *)value->data);
      } else if (field_type == INTS && value_type == CHARS) {  // to do qfs 不太确定要不要四舍五入？
        int data_i = round(strtof((char *)value->data, nullptr));
        memcpy(value->data, &data_i, sizeof(data_i));
      } else if (field_type == FLOATS && value_type == INTS) {
        int data_i = *(int *)value->data;
        float data_f = data_i * 1.0;
        memcpy(value->data, &data_f, sizeof(data_f));
      } else if (field_type == FLOATS && value_type == CHARS) {
        float data_f = strtof((char *)value->data, nullptr);
        memcpy(value->data, &data_f, sizeof(data_f));
      } else if (field_type == CHARS && value_type == INTS) {
        int data_i = *(int *)value->data;
        sprintf((char *)value->data, "%d", data_i);
      } else if (field_type == CHARS && value_type == FLOATS) {  // to do qfs 可能会有数太大用e表示的问题？
        float data_f = *(float *)value->data;
        sprintf((char *)value->data, "%g", data_f);
      } else {
        LOG_WARN("other type cast!");
      }
    }
    size_t copy_len = fields[i]->len();
    if (fields[i]->type() == CHARS) {
      const size_t data_len = strlen((const char *)update_stmt_->value(i)->data);
      if (copy_len > data_len) {
        copy_len = data_len + 1;
      }
    }
    copy_lens[i] = copy_len;
  }

  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple()[0];
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();

    char *record_data = record.data();
    for (size_t i = 0; i < field_num; i++) {
      memcpy(record_data + fields[i]->offset(), update_stmt_->value(i)->data, copy_lens[i]);
    }
    record.set_data(record_data);

    rc = table->update_record(trx_, &record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC UpdateOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}