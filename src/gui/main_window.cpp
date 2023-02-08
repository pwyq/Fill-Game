#include <QMenu>

// own include
#include "gui/main_window.h"


namespace GUI
{


MainWindow::MainWindow()
{
    // UI elements
    _layout     = new QGridLayout();
    _widget     = new QWidget();
    _menuBar    = new QMenuBar();

    this->initUI();
    this->setAttribute( Qt::WA_DeleteOnClose );
}

MainWindow::~MainWindow()
{
    // any possible clean up here
}

void MainWindow::initUI()
{
    this->setWindowTitle(QString::fromStdString("Fill Game"));

    this->setWindowSize(0.56, 0.50);

    QMenu* boardMenu = new QMenu();
    boardMenu->addMenu("&Board");
    _menuBar->addMenu(boardMenu);

    // temporary
    _boardHeight = 10;
    _boardWidth  = 10;

    for (uint8_t row = 0; row < _boardHeight; row++) {
        for (uint8_t col = 0; col < _boardWidth; col++) {
            QString t = "";
            BoardCell* button = new BoardCell(t, QPoint(row, col), this);
            _boardVec.push_back(button);
            connect(button, &QPushButton::pressed, [button, this](){
                this->onBoardCellPressed(button);
            });

            _layout->addWidget(button, row, col, 1, 1);
        }
    }

    _widget->setLayout(_layout);
    this->setCentralWidget(_widget);
}

void MainWindow::onBoardCellPressed(BoardCell* cell)
{
    std::cout << "pressed" << cell->getPos().x() << ", " << cell->getPos().y() << std::endl;
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