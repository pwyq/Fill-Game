#include "gui/board_cell.h"
#include "gui/helper.h"

#include <QDebug>

namespace GUI
{

BoardCell::BoardCell(QString& text, const QPoint& pos, QWidget* parent):
    QPushButton(text, parent),
    _pos(pos)
{
    if (text == "") {
        _value = 0;
    } else {
        _value = QStringToUint8(text);
        assert (_value >= 1 && _value <= 9);
    }

    const QSize BUTTON_SIZE = QSize(50, 50);
    this->setFixedSize(BUTTON_SIZE);
}

BoardCell::~BoardCell()
{
    qDebug() << "b1";
}

uint8_t BoardCell::getValue()
{
    return _value;
}

QString BoardCell::getText()
{
    return uint8ToQstring(_value);
}

const QPoint BoardCell::getPos()
{
    return _pos;
}
    
} // namespace GUI

