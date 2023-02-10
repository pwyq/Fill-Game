/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:27:59
 * @modify date 2023-02-10 05:27:59
 * @desc Popup selection for moves.
 *
 * TODO: keyboard input
 */
#ifndef FG_GUI_POPUP_SELECTION_H_
#define FG_GUI_POPUP_SELECTION_H_
// Qt
#include <QGridLayout>
#include <QMainWindow>
// std
#include <mutex>
#include <thread>
#include <vector>

namespace gui {

class PopupSelection : public QMainWindow {
  Q_OBJECT
  ///////////// Singleton /////////////
 private:
  static PopupSelection *pinstance_;
  static std::mutex mutex_;

 protected:
  PopupSelection(std::vector<uint8_t> available_moves);

 public:
  PopupSelection(PopupSelection &other) = delete;   // non-clonable
  void operator=(const PopupSelection &) = delete;  // non-assignable
  static PopupSelection *GetInstance(std::vector<uint8_t> available_moves);
  ~PopupSelection();
  /////////////////////////////////////
 protected:
  QGridLayout *layout_;
  QWidget *widget_;

 private:
  void initUI(std::vector<uint8_t> available_moves);
 signals:
  void selectedNumber(QString s);
};

}  // namespace gui

#endif  // FG_GUI_POPUP_SELECTION_H_