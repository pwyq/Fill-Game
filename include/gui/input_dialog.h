#ifndef __INPUT_DIALOG_H__
#define __INPUT_DIALOG_H__

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

namespace GUI
{


// class QLineEdit;
// class QLabel;

// https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qt
class InputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InputDialog(QWidget *parent = nullptr);

    static QStringList getStrings(QWidget *parent, bool *ok = nullptr);

private:
    QList<QLineEdit*> fields;
};


} // namespace GUI


#endif