#ifndef __POPUP_SELECITON_H__
#define __POPUP_SELECITON_H__

#include <QMainWindow>
#include <QGridLayout>

#include <vector>


namespace GUI
{

class PopupSelection: public QMainWindow
{
Q_OBJECT
public:
    PopupSelection(std::vector<uint8_t> available_moves);
    ~PopupSelection();
protected:
    QGridLayout* _layout;
    QWidget* _widget;
private:
    void initUI(std::vector<uint8_t> available_moves);
signals:
    void selectedNumber(QString s);
};

} // namespace GUI


#endif