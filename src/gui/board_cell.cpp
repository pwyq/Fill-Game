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

namespace gui {

BoardCell::BoardCell(QString &text, const QPoint &pos, QWidget *parent)
    : QPushButton(text, parent), pos_(pos) {
  if (text == "") {
    value_ = 0;
  } else {
    value_ = QStringToUint8(text);
    assert(value_ >= 1 && value_ <= 9);
  }

  this->setFixedSize(BUTTON_SIZE_);
}

BoardCell::~BoardCell() {}

void BoardCell::setText(const QString &text, uint8_t player) {
  switch (player) {
    case 0:  // black
      this->setStyleSheet("QPushButton {background-color: #bfbfbf; color: #000000}");
      break;
    case 1:  // white
      this->setStyleSheet("QPushButton {background-color: #d9d9d9; color: #000000}");
      break;
    default:
      this->setStyleSheet("QPushButton {background-color: #ffffff; color: #000000}");
      break;
  }
  QPushButton::setText(text);
}

}  // namespace gui
