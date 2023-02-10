#ifndef FG_INPUT_DIALOG_H_
#define FG_INPUT_DIALOG_H_

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

namespace GUI {

// class QLineEdit;
// class QLabel;

// https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qt
class InputDialog : public QDialog {
  Q_OBJECT
public:
  explicit InputDialog(QWidget *parent = nullptr);

  static QStringList getStrings(QWidget *parent, bool *ok = nullptr);

private:
  QList<QLineEdit *> fields;
};

} // namespace GUI

#endif // FG_INPUT_DIALOG_H_