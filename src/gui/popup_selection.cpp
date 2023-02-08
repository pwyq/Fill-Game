#include <QPushButton>
#include <QDebug>
#include "gui/popup_selection.h"


namespace GUI
{

// Singleton stuff
PopupSelection* PopupSelection::pinstance_{nullptr};
std::mutex PopupSelection::mutex_;


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
    qDebug() << "p1";
    delete _layout;
    qDebug() << "p2";

    delete _widget;
    qDebug() << "p3";

    pinstance_ = nullptr;
    qDebug() << "p4";

}

PopupSelection* PopupSelection::GetInstance(std::vector<uint8_t> available_moves)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr) {
        pinstance_ = new PopupSelection(available_moves);
    }
    return pinstance_;
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
