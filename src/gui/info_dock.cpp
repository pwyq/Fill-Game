/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-22 23:41:55
 * @modify date 2023-03-23 02:53:35
 */
#include "gui/info_dock.h"
// std
#include <iostream>
// Qt
#include <QDebug>
#include <QFile>
#include <QTextStream>

namespace gui {

///////////// Singleton /////////////
InfoDock *InfoDock::pinstance_{nullptr};
std::mutex InfoDock::mutex_;

InfoDock::InfoDock() {
  // UI elements
  layout_ = new QGridLayout();
  widget_ = new QWidget();

  playerW_      = new QLabel("WHITE");
  playerB_      = new QLabel("BLACK");
  timerB_       = new QTimer(this);
  timerW_       = new QTimer(this);
  timerB_label_ = new QLabel();
  timerW_label_ = new QLabel();
  timeB_        = QTime();
  timeW_        = QTime();
  browser_      = new QTextBrowser();

  this->initUI();
  this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
}

InfoDock::~InfoDock() { pinstance_ = nullptr; }

InfoDock *InfoDock::GetInstance() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) {
    pinstance_ = new InfoDock();
  }
  return pinstance_;
}
/////////////////////////////////////

void InfoDock::initUI() {
  this->setTitleBarWidget(new QWidget());
  this->loadQSS();

  playerB_->setEnabled(true);  // always black first
  playerW_->setEnabled(false);
  playerB_->setAlignment(Qt::AlignCenter);
  playerW_->setAlignment(Qt::AlignCenter);
  layout_->addWidget(playerB_, 0, 0, 2, 2);
  layout_->addWidget(playerW_, 0, 2, 2, 2);

  this->setCountdownTime();
  connect(timerB_, &QTimer::timeout, this, &InfoDock::onBlackTimeout);
  timerB_label_->setText(timeB_.toString(timer_format));
  timerB_label_->setAlignment(Qt::AlignCenter);
  timerB_label_->setObjectName("TIMER");
  layout_->addWidget(timerB_label_, 2, 0, 1, 2);

  connect(timerW_, &QTimer::timeout, this, &InfoDock::onWhiteTimeout);
  timerW_label_->setText(timeW_.toString(timer_format));
  timerW_label_->setAlignment(Qt::AlignCenter);
  timerW_label_->setObjectName("TIMER");
  layout_->addWidget(timerW_label_, 2, 2, 1, 2);

  layout_->addWidget(browser_, 3, 0, 4, 4);

  layout_->setContentsMargins(0, 0, 10, 10);
  widget_->setLayout(layout_);
  this->setWidget(widget_);
  this->setAllowedAreas(Qt::LeftDockWidgetArea);
  this->setFloating(false);
  this->setMinimumWidth(300);
}

void InfoDock::resetPlayer() {
  playerW_->setEnabled(false);
  playerB_->setEnabled(true);

  this->resetTimerUI();
  timerB_->start(1000);
}

void InfoDock::updatePlayer() {
  this->resetTimerUI();
  if (playerW_->isEnabled()) {
    playerW_->setEnabled(false);
    playerB_->setEnabled(true);

    timerW_->stop();
    timerB_->start(1000);
  } else {
    playerW_->setEnabled(true);
    playerB_->setEnabled(false);

    timerB_->stop();
    timerW_->start(1000);
  }
}

QString InfoDock::getCurrentPlayer() {
  return (playerW_->isEnabled()) ? "WHITE" : "BLACK";
}

void InfoDock::resetTimerUI() {
  this->setCountdownTime();
  timerB_label_->setText(timeB_.toString(timer_format));
  timerW_label_->setText(timeW_.toString(timer_format));
}

void InfoDock::setCountdownTime() {
  uint32_t hours, minutes;
  minutes    = countdown_ / 60;
  hours      = minutes / 60;
  hours      = int(hours);
  minutes    = int(minutes % 60);
  countdown_ = int(countdown_ % 60);  // seconds

  timeB_.setHMS(hours, minutes, countdown_);
  timeW_.setHMS(hours, minutes, countdown_);
}

void InfoDock::loadQSS() {
  QFile styleFile(":/resource/custom_qss/info_dock.qss");
  if (styleFile.open(QIODevice::ReadOnly)) {
    QTextStream ts(&styleFile);
    QString ss = ts.readAll();
    styleFile.close();
    this->setStyleSheet(ss);
  }
}

// Qt slots

void InfoDock::onStopGameTimer() {
  timerB_->stop();
  timerW_->stop();
}

void InfoDock::onBlackTimeout() {
  timeB_ = timeB_.addSecs(-1);
  timerB_label_->setText(timeB_.toString(timer_format));
  // if (timeB_.second() == 0) {
  //   timerB_->stop();
  //   emit this->gameTimeOut("BLACK lost due to time out!");
  // }
}

void InfoDock::onWhiteTimeout() {
  timeW_ = timeW_.addSecs(-1);
  timerW_label_->setText(timeW_.toString(timer_format));
  // if (timeW_.second() == 0) {
  //   timerW_->stop();
  //   emit this->gameTimeOut("WHITE lost due to time out!");
  // }
}

}  // namespace gui
