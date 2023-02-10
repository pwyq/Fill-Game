/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:31:33
 * @modify date 2023-02-10 05:31:33
 */
#include "gui/board_cell.h"
// Qt
#include <QDebug>
// local
#include "gui/helper.h"

namespace GUI {

BoardCell::BoardCell(QString &text, const QPoint &pos, QWidget *parent)
    : QPushButton(text, parent), _pos(pos) {
  if (text == "") {
    _value = 0;
  } else {
    _value = QStringToUint8(text);
    assert(_value >= 1 && _value <= 9);
  }

  const QSize BUTTON_SIZE = QSize(50, 50);
  this->setFixedSize(BUTTON_SIZE);
}

BoardCell::~BoardCell() {}

inline uint8_t BoardCell::getValue() { return _value; }

inline QString BoardCell::getText() { return uint8ToQstring(_value); }

inline const QPoint BoardCell::getPos() { return _pos; }

}  // namespace GUI
