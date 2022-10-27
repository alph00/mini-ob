//
// Created by hsy on 22-10-26.
//

#include "common/log/log.h"
#include "sql/operator/update_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"

RC UpdateOperator::open() {
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
  const char* field_name = update_stmt_->field_name();
  const FieldMeta *field = table->table_meta().field(field_name);
  const Value *value = update_stmt_->value();
  size_t copy_len = field->len();
  if (field->type() == CHARS) {
    const size_t data_len = strlen((const char *)value->data);
    if (copy_len > data_len) {
      copy_len = data_len + 1;
    }
  }

  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();

    char *record_data = record.data();
    memcpy(record_data + field->offset(), value->data, copy_len);
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