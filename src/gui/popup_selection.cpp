#include <QPushButton>

#include "gui/popup_selection.h"


namespace GUI
{

PopupSelection::PopupSelection(std::vector<uint8_t> available_moves)
{
    // UI elements
    _layout     = new QGridLayout();
    _widget     = new QWidget();
    this->initUI(available_moves);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute( Qt::WA_DeleteOnClose );
}

PopupSelection::~PopupSelection()
{
    delete _layout;
    delete _widget;
}

void PopupSelection::initUI(std::vector<uint8_t> available_moves)
{
    int row = 0;
    int col = 0;
    for (auto move: available_moves) {
        QPushButton* button = new QPushButton(QString::fromStdString(std::to_string(move)));
        _layout->addWidget(button, row, col++, 1, 1);
        if (col == 5) {
            row += 1;
            col = 0;
        }
        connect(button, &QPushButton::pressed, [button, this](){
            emit this->selectedNumber(button->text());
        });
    }
    _widget->setLayout(_layout);
    this->setCentralWidget(_widget);
}


} // namespace GUI