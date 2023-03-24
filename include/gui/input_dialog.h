/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:26:47
 * @modify date 2023-03-23 17:57:35
 * @desc Multiple input dialogs
 */
#ifndef FG_INPUT_DIALOG_H_
#define FG_INPUT_DIALOG_H_
// Qt
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QSpinBox>

namespace gui {

// class QLineEdit; // forward declaration
// class QLabel;

// https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qt
class InputDialog : public QDialog {
  Q_OBJECT
 public:
  explicit InputDialog(QWidget *parent = nullptr);

  static std::pair<uint8_t, uint8_t> getInputs(QWidget *parent, bool *ok = nullptr);

 private:
  QStringList labels_ = {"Width", "Height"};
  QList<QSpinBox *> fields_;
};

}  // namespace gui

#endif  // FG_INPUT_DIALOG_H_