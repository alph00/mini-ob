//
// Created by hsy on 22-10-26.
//

#include "common/log/log.h"
#include "sql/operator/update_operator.h"
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