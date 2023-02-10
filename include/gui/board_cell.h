/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:24:49
 * @modify date 2023-02-10 05:24:51
 * @desc Custom QPushButton as a board cell for the game board.
 */
#ifndef FG_GUI_BOARD_CELL_H_
#define FG_GUI_BOARD_CELL_H_

// Qt
#include <QPushButton>
// local
#include "gui/helper.h"

namespace GUI {

class BoardCell : public QPushButton {
 public:
  BoardCell(QString &text, const QPoint &pos, QWidget *parent = 0);
  ~BoardCell();

  inline uint8_t getValue();
  inline QString getText();
  inline const QPoint getPos();

 private:
  uint8_t _value;
  QPoint _pos;
};

inline uint8_t BoardCell::getValue() { return _value; }

inline QString BoardCell::getText() { return uint8ToQstring(_value); }

inline const QPoint BoardCell::getPos() { return _pos; }

}  // namespace GUI

#endif  // FG_GUI_BOARD_CELL_H_