#ifndef __BOARD_CELL_H__
#define __BOARD_CELL_H__

#include <QPushButton>

namespace GUI
{
    
class BoardCell : public QPushButton
{

public:
    BoardCell(QString& text, const QPoint& pos, QWidget* parent = 0);
    ~BoardCell();

    uint8_t getValue();
    QString getText();
    const QPoint getPos();
private:
    uint8_t _value;
    QPoint _pos;

};

} // namespace GUI



#endif