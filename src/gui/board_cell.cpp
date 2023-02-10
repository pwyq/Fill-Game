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

}  // namespace gui
