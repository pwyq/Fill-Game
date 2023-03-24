/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:32:16
 * @modify date 2023-03-23 17:57:32
 */
// local
#include "gui/input_dialog.h"

#include <QLabel>

namespace gui {

InputDialog::InputDialog(QWidget *parent) : QDialog(parent) {
  QFormLayout *lytMain = new QFormLayout(this);

  for (int i = 0; i < 2; i++) {
    QSpinBox *box = new QSpinBox(this);
    QLabel *label = new QLabel(labels_[i]);
    box->setValue(5);
    box->setMinimum(1);
    box->setMaximum(19);
    box->setSingleStep(1);
    lytMain->addRow(label, box);
    fields_ << box;
  }

  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
  lytMain->addWidget(buttonBox);

  bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this, &InputDialog::accept);
  Q_ASSERT(conn);
  conn = connect(buttonBox, &QDialogButtonBox::rejected, this, &InputDialog::reject);
  Q_ASSERT(conn);

  setLayout(lytMain);
}

std::pair<uint8_t, uint8_t> InputDialog::getInputs(QWidget *parent, bool *ok) {
  InputDialog *dialog = new InputDialog(parent);

  std::pair<uint8_t, uint8_t> res;

  const int ret = dialog->exec();
  if (ok) *ok = !!ret;

  if (ret) {
    res = std::make_pair(dialog->fields_[0]->value(), dialog->fields_[1]->value());
  }

  dialog->deleteLater();

  return res;
}

}  // namespace gui
