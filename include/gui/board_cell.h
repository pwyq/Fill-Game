#ifndef FG_GUI_BOARD_CELL_H_
#define FG_GUI_BOARD_CELL_H_


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


#endif  // FG_GUI_BOARD_CELL_H_