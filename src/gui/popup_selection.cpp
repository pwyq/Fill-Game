/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:33:17
 * @modify date 2023-03-23 02:56:38
 */
#include "gui/popup_selection.h"
// Qt
#include <QDebug>
#include <QPushButton>

namespace gui {

///////////// Singleton /////////////
PopupSelection *PopupSelection::pinstance_{nullptr};
std::mutex PopupSelection::mutex_;

PopupSelection::PopupSelection(std::vector<uint8_t> available_moves)
    : moves_(available_moves) {
  // UI elements
  layout_ = new QGridLayout();
  widget_ = new QWidget();
  this->initUI();
  this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
}

PopupSelection::~PopupSelection() {
  // https://www.techiedelight.com/delete-vector-free-memory-cpp/
  moves_.clear();
  moves_.shrink_to_fit();

  pinstance_ = nullptr;
}

PopupSelection *PopupSelection::GetInstance(std::vector<uint8_t> available_moves) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) {
    pinstance_ = new PopupSelection(available_moves);
  }
  return pinstance_;
}

/////////////////////////////////////

void PopupSelection::initUI() {
  uint8_t row = 0;
  uint8_t col = 0;
  for (auto move : moves_) {
    QPushButton *button = new QPushButton(QString::fromStdString(std::to_string(move)));
    layout_->addWidget(button, row, col++, 1, 1);
    if (col == 5) {
      row += 1;
      col = 0;
    }
    connect(button, &QPushButton::pressed, [button, this]() {
      emit this->selectedNumber(button->text());
    });
  }
  widget_->setLayout(layout_);
  this->setCentralWidget(widget_);
}

void PopupSelection::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_1:
      if (isValidKey(1)) emit this->selectedNumber("1");
      break;
    case Qt::Key_2:
      if (isValidKey(2)) emit this->selectedNumber("2");
      break;
    case Qt::Key_3:
      if (isValidKey(3)) emit this->selectedNumber("3");
      break;
    case Qt::Key_4:
      if (isValidKey(4)) emit this->selectedNumber("4");
      break;
    case Qt::Key_5:
      if (isValidKey(5)) emit this->selectedNumber("5");
      break;
    case Qt::Key_6:
      if (isValidKey(6)) emit this->selectedNumber("6");
      break;
    case Qt::Key_7:
      if (isValidKey(7)) emit this->selectedNumber("7");
      break;
    case Qt::Key_8:
      if (isValidKey(8)) emit this->selectedNumber("8");
      break;
    case Qt::Key_9:
      if (isValidKey(9)) emit this->selectedNumber("9");
      break;
  }
}

bool PopupSelection::isValidKey(uint8_t key) {
  for (auto m : moves_) {
    if (m == key) {
      return true;
    }
  }
  return false;
}

}  // namespace gui
