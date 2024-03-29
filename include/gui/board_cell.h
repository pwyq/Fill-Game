/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:24:49
 * @modify date 2023-03-23 16:23:01
 * @desc Custom QPushButton as a board cell for the game board.
 */
#ifndef FG_GUI_BOARD_CELL_H_
#define FG_GUI_BOARD_CELL_H_

// Qt
#include <QPushButton>
// local
#include "gui/helper.h"

namespace gui {

class BoardCell : public QPushButton {
 public:
  BoardCell(QString &text, const QPoint &pos, QWidget *parent = 0);
  ~BoardCell();

  inline uint8_t getValue() const { return value_; };
  inline QString getText() const { return helper::uint8ToQstring(value_); };
  inline const QPoint getPos() const { return pos_; };

  void setText(const QString &text, uint8_t player = 7);  // as long as default is not 0 and 1

 private:
  uint8_t value_;
  QPoint pos_;
  const QSize BUTTON_SIZE_ = QSize(50, 50);
};

}  // namespace gui

#endif  // FG_GUI_BOARD_CELL_H_