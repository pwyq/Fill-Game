/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-22 23:41:55
 * @modify date 2023-03-23 00:30:11
 */
#include "gui/info_dock.h"
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

  playerW_ = new QLabel("WHITE");
  playerB_ = new QLabel("BLACK");
  browser_ = new QTextBrowser();

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

  QFile styleFile(":/resource/custom_qss/info_dock.qss");
  if (styleFile.open(QIODevice::ReadOnly)) {
    QTextStream ts(&styleFile);
    QString ss = ts.readAll();
    styleFile.close();
    this->setStyleSheet(ss);
  }

  playerW_->setEnabled(false);
  playerB_->setEnabled(true);  // always black first
  playerW_->setAlignment(Qt::AlignCenter);
  playerB_->setAlignment(Qt::AlignCenter);
  layout_->addWidget(playerW_, 0, 0, 2, 2);
  layout_->addWidget(playerB_, 0, 2, 2, 2);
  layout_->addWidget(browser_, 2, 0, 4, 4);

  layout_->setContentsMargins(0, 0, 0, 0);
  widget_->setLayout(layout_);
  this->setWidget(widget_);
  this->setAllowedAreas(Qt::LeftDockWidgetArea);
  this->setFloating(false);
}

void InfoDock::resetPlayer() {
  playerW_->setEnabled(false);
  playerB_->setEnabled(true);
}

void InfoDock::updatePlayer() {
  if (playerW_->isEnabled()) {
    playerW_->setEnabled(false);
    playerB_->setEnabled(true);
  } else {
    playerW_->setEnabled(true);
    playerB_->setEnabled(false);
  }
}

QString InfoDock::getCurrentPlayer() {
  return (playerW_->isEnabled()) ? "WHITE" : "BLACK";
}

}  // namespace gui
