/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:33:17
 * @modify date 2023-02-10 05:33:17
 */
#include "gui/popup_selection.h"
// Qt
#include <QDebug>
#include <QPushButton>

namespace gui {

// Singleton stuff
PopupSelection *PopupSelection::pinstance_{nullptr};
std::mutex PopupSelection::mutex_;

PopupSelection::PopupSelection(std::vector<uint8_t> available_moves) {
  // UI elements
  layout_ = new QGridLayout();
  widget_ = new QWidget();
  this->initUI(available_moves);
  this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
}

PopupSelection::~PopupSelection() { pinstance_ = nullptr; }

PopupSelection *PopupSelection::GetInstance(
    std::vector<uint8_t> available_moves) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) {
    pinstance_ = new PopupSelection(available_moves);
  }
  return pinstance_;
}

void PopupSelection::initUI(std::vector<uint8_t> available_moves) {
  uint8_t row = 0;
  uint8_t col = 0;
  for (auto move : available_moves) {
    QPushButton *button =
        new QPushButton(QString::fromStdString(std::to_string(move)));
    layout_->addWidget(button, row, col++, 1, 1);
    if (col == 5) {
      row += 1;
      col = 0;
    }
    connect(button, &QPushButton::pressed,
            [button, this]() { emit this->selectedNumber(button->text()); });
  }
  widget_->setLayout(layout_);
  this->setCentralWidget(widget_);
}

}  // namespace gui
