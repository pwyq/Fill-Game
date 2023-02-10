/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:26:47
 * @modify date 2023-02-10 05:26:47
 * @desc Multiple input dialogs
 */
#ifndef FG_INPUT_DIALOG_H_
#define FG_INPUT_DIALOG_H_
// Qt
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

namespace GUI {

// class QLineEdit; // forward declaration
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

}  // namespace GUI

#endif  // FG_INPUT_DIALOG_H_