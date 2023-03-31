/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-26 13:10:25
 * @modify date 2023-03-26 13:10:25
 */

#include "gui/new_game_window.h"
// Qt
#include <QLabel>
// local
#include "gui/input_dialog.h"

namespace gui {

///////////// Singleton /////////////
NewGameWindow *NewGameWindow::pinstance_{nullptr};
std::mutex NewGameWindow::mutex_;

NewGameWindow::NewGameWindow() {
  // UI elements
  layout_ = new QGridLayout();
  widget_ = new QWidget();

  this->initUI();
  this->setAttribute(Qt::WA_DeleteOnClose);
}

NewGameWindow::~NewGameWindow() { pinstance_ = nullptr; }

NewGameWindow *NewGameWindow::GetInstance() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) {
    pinstance_ = new NewGameWindow();
  }
  return pinstance_;
}
/////////////////////////////////////

void NewGameWindow::initUI() {
  this->setWindowTitle("Start a New Game");
  this->setWindowSize(0.56, 0.50);

  int layout_row = 0;
  int layout_col = 0;
  layout_->addWidget(new QLabel("Board Size"), layout_row, layout_col++, 1, 1);
  size_group_ = new QButtonGroup(this);
  connect(size_group_, qOverload<int>(&QButtonGroup::buttonClicked), this, &NewGameWindow::onSizeGroupClicked);
  size_group_->addButton(createPushButton("3x3"));
  size_group_->addButton(createPushButton("5x5"));
  size_group_->addButton(createPushButton("7x7"));
  size_group_->addButton(createPushButton("10x10"));
  size_group_->addButton(createPushButton("?x?"));
  QList<QAbstractButton *> buttonList = size_group_->buttons();
  for (QList<QAbstractButton *>::const_iterator it = buttonList.cbegin(); it != buttonList.cend(); ++it) {
    layout_->addWidget(*it, layout_row, layout_col++);
  }
  buttonList.clear();

  layout_row += 1;
  layout_col = 0;

  layout_->addWidget(new QLabel("Opponent"), layout_row, layout_col++, 1, 1);

  opponent_group_ = new QButtonGroup(this);
  connect(opponent_group_, qOverload<int>(&QButtonGroup::buttonClicked), this, &NewGameWindow::onOpponentGroupClicked);
  opponent_group_->addButton(createPushButton("PNS", false));
  opponent_group_->addButton(createPushButton("DFPN"));
  opponent_group_->addButton(createPushButton("MINIMAX+AB+TT", false));
  opponent_group_->addButton(createPushButton("NEGAMAX+AB+TT", false));
  opponent_group_->addButton(createPushButton("Human (remote)"));
  opponent_group_->addButton(createPushButton("Human (local)"));
  buttonList = opponent_group_->buttons();
  for (QList<QAbstractButton *>::const_iterator it = buttonList.cbegin(); it != buttonList.cend(); ++it) {
    layout_->addWidget(*it, layout_row, layout_col++);
  }

  layout_row += 1;
  layout_col = 0;

  layout_->addWidget(new QLabel("Board Value"), layout_row, layout_col++, 1, 1);
  value_group_ = new QButtonGroup(this);
  connect(value_group_, qOverload<int>(&QButtonGroup::buttonClicked), this, &NewGameWindow::onValueGroupClicked);
  value_group_->addButton(createPushButton("4"));
  value_group_->addButton(createPushButton("5", false));
  value_group_->addButton(createPushButton("6", false));
  value_group_->addButton(createPushButton("7", false));
  value_group_->addButton(createPushButton("8", false));
  value_group_->addButton(createPushButton("9", false));
  buttonList = value_group_->buttons();
  for (QList<QAbstractButton *>::const_iterator it = buttonList.cbegin(); it != buttonList.cend(); ++it) {
    layout_->addWidget(*it, layout_row, layout_col++);
  }

  widget_->setLayout(layout_);
  this->setCentralWidget(widget_);
}

QPushButton *NewGameWindow::createPushButton(QString name, bool is_enabled) {
  QPushButton *res = new QPushButton(name);
  res->setEnabled(is_enabled);
  return res;
}

///////////////////////////////////////
// Qt slots
///////////////////////////////////////

void NewGameWindow::onSizeGroupClicked(int id) {
  // https://doc.qt.io/qt-6/qbuttongroup.html#addButton
  // auto-assigned id starts with -2
  for (int i = -2; i >= -6; i--) {
    if (id == i) {
      size_group_->button(id)->setStyleSheet("QPushButton{ background-color: cyan}");
    } else {
      size_group_->button(i)->setStyleSheet("");
    }
  }
  switch (id) {
    case -2:  // 3x3
      emit this->changeGameSize(3, 3);
      break;
    case -3:  // 5x5
      emit this->changeGameSize(5, 5);
      break;
    case -4:  // 7x7
      emit this->changeGameSize(7, 7);
      break;
    case -5:  //10x10
      emit this->changeGameSize(10, 10);
      break;
    case -6: {  // ?x?
      std::pair<uint8_t, uint8_t> res = InputDialog::getInputs(this);
      if (res.first != 0 && res.second != 0) {
        emit this->changeGameSize(res.first, res.second);
      }
      break;
    }
    default:
      break;
  }
}

void NewGameWindow::onOpponentGroupClicked(int id) {
  for (int i = -2; i >= -7; i--) {
    if (id == i) {
      opponent_group_->button(id)->setStyleSheet("QPushButton{ background-color: cyan}");
    } else {
      opponent_group_->button(i)->setStyleSheet("");
    }
  }
  switch (id) {
    case -2:  // PNS
      emit this->selectOpponent(helper::SOLVER::PNS);
      break;
    case -3:  // DFPN
      emit this->selectOpponent(helper::SOLVER::DFPN);
      break;
    case -4:  // MINIMAX
      emit this->selectOpponent(helper::SOLVER::MINIMAX_AB_TT);
      break;
    case -5:  // NEGAMAX
      emit this->selectOpponent(helper::SOLVER::NEGAMAX_AB_TT);
      break;
    case -6:  // Human remote
      emit this->selectOpponent(helper::SOLVER::HUMAN_REMOTE);
      break;
    case -7:  // Human local
      emit this->selectOpponent(helper::SOLVER::HUMAN_LOCAL);
      break;
    default:
      break;
  }
}

/**
 * @brief change the number of values for a cell
 *        TODO: will need to modify Game() class to take other options
 * 
 * @param id 
 */
void NewGameWindow::onValueGroupClicked(int id) {
  for (int i = -2; i >= -7; i--) {
    if (id == i) {
      value_group_->button(id)->setStyleSheet("QPushButton{ background-color: cyan}");
    } else {
      value_group_->button(i)->setStyleSheet("");
    }
  }
  switch (id) {
    case -2:  // 4
      break;
    case -3:  // 5
      break;
    case -4:  // 6
      break;
    case -5:  // 7
      break;
    case -6:  // 8
      break;
    case -7:  // 9
      break;
    default:
      break;
  }
}

}  // namespace gui
