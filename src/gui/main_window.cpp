// Qt include
// #include <QDesktopWidget>

// own include
#include "gui/main_window.h"

namespace GUI
{


MainWindow::MainWindow(const std::string& title, const std::string& htmlPath)
{
    // UI elements
    layout_     = new QGridLayout();
    widget_     = new QWidget();
    browser_    = new QTextBrowser(this);

    this->initUI(title, htmlPath);
    this->setAttribute( Qt::WA_DeleteOnClose );
}

MainWindow::~MainWindow()
{
    // any possible clean up here
}

void MainWindow::initUI(const std::string& title, const std::string& htmlPath)
{
    this->setWindowTitle(QString::fromStdString(title));

    this->setWindowSize(0.56, 0.50);

    browser_->setOpenExternalLinks(false);
    browser_->setSource(QUrl(QString::fromStdString(htmlPath)));
    layout_->addWidget(browser_, 0, 0);

    widget_->setLayout(layout_);
    this->setCentralWidget(widget_);
}

/**
 * @brief set window size based on width/height ratio to user screen resolution
 * 
 * @param widthRatio 
 * @param heightRatio 
 */
void MainWindow::setWindowSize(const float& widthRatio, const float& heightRatio)
{
    assert(0 <= widthRatio  && widthRatio  < 1);
    assert(0 <= heightRatio && heightRatio < 1);
    // QDesktopWidget dw;
    // float ww = widthRatio * dw.availableGeometry().width();
    // float hh = heightRatio * dw.availableGeometry().height();
    // this->setFixedSize(QSize(ww, hh));
}


} // namespace GUI