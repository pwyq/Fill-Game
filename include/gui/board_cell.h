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

namespace GUI {

class BoardCell : public QPushButton {
 public:
  BoardCell(QString &text, const QPoint &pos, QWidget *parent = 0);
  ~BoardCell();

  uint8_t getValue();
  QString getText();
  const QPoint getPos();

 private:
  uint8_t _value;
  QPoint _pos;
};

}  // namespace GUI

#endif  // FG_GUI_BOARD_CELL_H_