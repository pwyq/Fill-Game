/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-26 13:10:25
 * @modify date 2023-03-31 16:06:14
 */

#include "gui/new_game_window.h"
// Qt
#include <QLabel>
#include <QStatusBar>
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
  layout_->addWidget(new QLabel(tr("Board Size")), layout_row, layout_col++, 1, 1);
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

  layout_->addWidget(new QLabel(tr("Opponent")), layout_row, layout_col++, 1, 1);

  opponent_group_ = new QButtonGroup(this);
  connect(opponent_group_, qOverload<int>(&QButtonGroup::buttonClicked), this, &NewGameWindow::onOpponentGroupClicked);
  opponent_group_->addButton(createPushButton("PNS"));
  opponent_group_->addButton(createPushButton("DFPN"));
  opponent_group_->addButton(createPushButton("MINIMAX+AB+TT"));
  opponent_group_->addButton(createPushButton("NEGAMAX+AB+TT"));
  opponent_group_->addButton(createPushButton("Human (remote)"));
  opponent_group_->addButton(createPushButton("Human (local)"));
  buttonList = opponent_group_->buttons();
  for (QList<QAbstractButton *>::const_iterator it = buttonList.cbegin(); it != buttonList.cend(); ++it) {
    layout_->addWidget(*it, layout_row, layout_col++);
  }

  layout_row += 1;
  layout_col = 0;

  layout_->addWidget(new QLabel(tr("Board Value")), layout_row, layout_col++, 1, 1);
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

  layout_row += 1;
  layout_col = 0;
  layout_->addWidget(new QLabel(tr("Your Color")), layout_row, layout_col++, 1, 1);
  color_group_ = new QButtonGroup(this);
  connect(color_group_, qOverload<int>(&QButtonGroup::buttonClicked), this, &NewGameWindow::onColorGroupClicked);
  color_group_->addButton(createPushButton("Black (1st)"));
  color_group_->addButton(createPushButton("White (2nd)"));
  color_group_->addButton(createPushButton("Random"));
  buttonList = color_group_->buttons();
  for (QList<QAbstractButton *>::const_iterator it = buttonList.cbegin(); it != buttonList.cend(); ++it) {
    layout_->addWidget(*it, layout_row, layout_col++);
  }

  layout_row += 1;
  layout_col = 3;

  start_button_ = new QPushButton(tr("Start"));
  connect(start_button_, &QPushButton::pressed, [this]() {
    emit this->startGame();
    this->close();
  });
  layout_->addWidget(start_button_, layout_row, layout_col);

  // layout_col += 2;
  // cancel_button_ = new QPushButton("Cancel");
  // connect(cancel_button_, &QPushButton::pressed, [this]() {
  //   this->close();
  // });
  // layout_->addWidget(cancel_button_, layout_row, layout_col);

  initDefaultConfiguration();

  widget_->setLayout(layout_);
  this->setCentralWidget(widget_);
}

void NewGameWindow::initDefaultConfiguration() {
  // TODO: QKey (remove hardcoded values)

  // 3x3
  size_group_->button(-2)->setStyleSheet("QPushButton{ background-color: cyan}");
  // DFPN
  opponent_group_->button(-3)->setStyleSheet("QPushButton{ background-color: cyan}");
  // 4
  value_group_->button(-2)->setStyleSheet("QPushButton{ background-color: cyan}");
  // random
  color_group_->button(-4)->setStyleSheet("QPushButton{ background-color: cyan}");
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
      statusBar()->showMessage(tr("Changed game board size to 3 by 3."), 2000);
      break;
    case -3:  // 5x5
      emit this->changeGameSize(5, 5);
      statusBar()->showMessage(tr("Changed game board size to 5 by 5."), 2000);
      break;
    case -4:  // 7x7
      emit this->changeGameSize(7, 7);
      statusBar()->showMessage(tr("Changed game board size to 7 by 7."), 2000);
      break;
    case -5:  //10x10
      emit this->changeGameSize(10, 10);
      statusBar()->showMessage(tr("Changed game board size to 10 by 10."), 2000);
      break;
    case -6: {  // ?x?
      std::pair<uint8_t, uint8_t> res = InputDialog::getInputs(this);
      if (res.first != 0 && res.second != 0) {
        emit this->changeGameSize(res.first, res.second);
        statusBar()->showMessage(tr("Changed game board size to %1 by %2.").arg(helper::uint8ToQstring(res.first), helper::uint8ToQstring(res.second)),
                                 2000);
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
  for (int i = -2; i >= -4; i--) {
    color_group_->button(i)->setEnabled(true);
  }

  switch (id) {
    case -2:  // PNS
      emit this->selectOpponent(helper::SOLVER::PNS);
      statusBar()->showMessage(tr("Changed opponent agent to PNS"), 2000);
      break;
    case -3:  // DFPN
      emit this->selectOpponent(helper::SOLVER::DFPN);
      statusBar()->showMessage(tr("Changed opponent agent to DFPN"), 2000);
      break;
    case -4:  // MINIMAX
      emit this->selectOpponent(helper::SOLVER::MINIMAX_AB_TT);
      statusBar()->showMessage(tr("Changed opponent agent to Minimax+AB+TT"), 2000);
      break;
    case -5:  // NEGAMAX
      emit this->selectOpponent(helper::SOLVER::NEGAMAX_AB_TT);
      statusBar()->showMessage(tr("Changed opponent agent to Negamax+AB+TT"), 2000);
      break;
    case -6:  // Human remote
      emit this->selectOpponent(helper::SOLVER::HUMAN_REMOTE);
      statusBar()->showMessage(tr("Changing opponent to human (remote). Ensure connection is made before start."));
      // and disable color selection for remote play // for now, whoever first press start, starts first
      for (int i = -2; i >= -4; i--) {
        color_group_->button(i)->setEnabled(false);
        color_group_->button(i)->setStyleSheet("");
      }
      break;
    case -7: {  // Human local
      emit this->selectOpponent(helper::SOLVER::HUMAN_LOCAL);
      statusBar()->showMessage(tr("Changed opponent to human (local)"), 2000);
      // and disable color selection for local play
      for (int i = -2; i >= -4; i--) {
        color_group_->button(i)->setEnabled(false);
        color_group_->button(i)->setStyleSheet("");
      }
      break;
    }
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
      statusBar()->showMessage(tr("Changed max value to 4"), 2000);
      break;
    case -3:  // 5
      statusBar()->showMessage(tr("Changed max value to 5"), 2000);
      break;
    case -4:  // 6
      statusBar()->showMessage(tr("Changed max value to 6"), 2000);
      break;
    case -5:  // 7
      statusBar()->showMessage(tr("Changed max value to 7"), 2000);
      break;
    case -6:  // 8
      statusBar()->showMessage(tr("Changed max value to 8"), 2000);
      break;
    case -7:  // 9
      statusBar()->showMessage(tr("Changed max value to 9"), 2000);
      break;
    default:  // 4
      statusBar()->showMessage(tr("Changed max value to 4"), 2000);
      break;
  }
}

void NewGameWindow::onColorGroupClicked(int id) {
  for (int i = -2; i >= -4; i--) {
    if (id == i) {
      color_group_->button(id)->setStyleSheet("QPushButton{ background-color: cyan}");
    } else {
      color_group_->button(i)->setStyleSheet("");
    }
  }

  switch (id) {
    case -2:  // black
      emit selectPlayerColor(PLAYER::BLACK);
      statusBar()->showMessage(tr("Changed player color to Black"), 2000);
      break;
    case -3:  // white
      statusBar()->showMessage(tr("Changed player color to White"), 2000);
      emit selectPlayerColor(PLAYER::WHITE);
      break;
    case -4: {  // random
      statusBar()->showMessage(tr("Changed player color to Random"), 2000);
      if (helper::randomBool()) {
        emit selectPlayerColor(PLAYER::BLACK);
      } else {
        emit selectPlayerColor(PLAYER::WHITE);
      }
      break;
    }
    default:  // black
      statusBar()->showMessage(tr("Changed player color to Black"), 2000);
      emit selectPlayerColor(PLAYER::BLACK);
      break;
  }
}

}  // namespace gui
