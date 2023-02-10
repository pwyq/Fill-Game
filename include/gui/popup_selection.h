#ifndef FG_GUI_POPUP_SELECTION_H_
#define FG_GUI_POPUP_SELECTION_H_


#include <QMainWindow>
#include <QGridLayout>

#include <vector>
#include <mutex>
#include <thread>


namespace GUI
{

class PopupSelection: public QMainWindow
{
Q_OBJECT
///////////// Singleton /////////////
private:
    static PopupSelection* pinstance_;
    static std::mutex mutex_;
protected:
    PopupSelection(std::vector<uint8_t> available_moves);
public:
    PopupSelection(PopupSelection& other)   = delete;   // non-clonable
    void operator=(const PopupSelection&)   = delete;   // non-assignable
    static PopupSelection* GetInstance(std::vector<uint8_t> available_moves);
    ~PopupSelection();
/////////////////////////////////////
protected:
    QGridLayout* _layout;
    QWidget* _widget;
private:
    void initUI(std::vector<uint8_t> available_moves);
signals:
    void selectedNumber(QString s);
};

} // namespace GUI


#endif  // FG_GUI_POPUP_SELECTION_H_