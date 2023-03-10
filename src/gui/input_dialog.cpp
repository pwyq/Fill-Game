/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:32:16
 * @modify date 2023-02-10 05:32:16
 */
// local
#include "gui/input_dialog.h"

namespace gui {

InputDialog::InputDialog(QWidget *parent) : QDialog(parent) {
  QFormLayout *lytMain = new QFormLayout(this);

  for (int i = 0; i < 4; ++i) {
    QLabel *tLabel = new QLabel(QString("Text_%1:").arg(i), this);
    QLineEdit *tLine = new QLineEdit(this);
    lytMain->addRow(tLabel, tLine);

    fields_ << tLine;
  }

  QDialogButtonBox *buttonBox = new QDialogButtonBox(
      QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
  lytMain->addWidget(buttonBox);

  bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this,
                      &InputDialog::accept);
  Q_ASSERT(conn);
  conn = connect(buttonBox, &QDialogButtonBox::rejected, this,
                 &InputDialog::reject);
  Q_ASSERT(conn);

  setLayout(lytMain);
}

QStringList InputDialog::getStrings(QWidget *parent, bool *ok) {
  InputDialog *dialog = new InputDialog(parent);

  QStringList list;

  const int ret = dialog->exec();
  if (ok) *ok = !!ret;

  if (ret) {
    foreach (auto field, dialog->fields_) { list << field->text(); }
  }

  dialog->deleteLater();

  return list;
}

}  // namespace gui
