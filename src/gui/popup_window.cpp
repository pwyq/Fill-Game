/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-11 11:13:23
 * @modify date 2023-02-11 11:45:28
 */
#include "gui/popup_window.h"

namespace gui {

PopupWindow::PopupWindow(const QString& title, const QString& htmlPath) {
  // UI elements
  layout_  = new QGridLayout();
  widget_  = new QWidget();
  browser_ = new QTextBrowser(this);

  this->initUI(title, htmlPath);
  this->setAttribute(Qt::WA_DeleteOnClose);
}

PopupWindow::~PopupWindow() {
  // any possible clean up here
}

void PopupWindow::initUI(const QString& title, const QString& htmlPath) {
  this->setWindowTitle(title);

  this->setWindowSize(0.56, 0.50);

  browser_->setOpenExternalLinks(true);
  browser_->setSource(QUrl(htmlPath));
  layout_->addWidget(browser_, 0, 0);

  widget_->setLayout(layout_);
  this->setCentralWidget(widget_);
}

}  // namespace gui

// EOF