// Qt
#include <QMenu>
#include <QMessageBox>

// own include
#include "gui/main_window.h"
#include "gui/popup_selection.h"


namespace GUI
{


MainWindow::MainWindow()
{
    // temporary
    _boardHeight = 2;
    _boardWidth  = 2;

    // UI elements
    _layout     = new QGridLayout();
    _widget     = new QWidget();
    _menuBar    = new QMenuBar();

    // Solver elements
    std::string _gameString = "";
    for (uint8_t row = 0; row < _boardHeight; row++) {
        for (uint8_t col = 0; col < _boardWidth; col++) {
            _gameString += ".";
        }
        _gameString += "*";
    }
    _gameString.pop_back();
    std::cout << _gameString << std::endl;
    _game       = new Game(_gameString);

    this->initUI();
    this->setAttribute( Qt::WA_DeleteOnClose );
}

MainWindow::~MainWindow()
{
    delete _layout;
    delete _widget;
    delete _menuBar;
    for (auto p : _boardVec) {
        delete p;
    }
    _boardVec.clear();
}

void MainWindow::initUI()
{
    this->setWindowTitle(QString::fromStdString("Fill Game"));

    this->setWindowSize(0.56, 0.50);

    // TODO: menu bar
    QMenu* boardMenu = new QMenu();
    boardMenu->addMenu("&Board");
    _menuBar->addMenu(boardMenu);

    for (uint8_t row = 0; row < _boardHeight; row++) {
        for (uint8_t col = 0; col < _boardWidth; col++) {
            QString t = "";
            BoardCell* button = new BoardCell(t, QPoint(col, row), this);   // note that col=x, row=y, from top down
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
    Pos cellPos = Pos{
        static_cast<uint8_t>(cell->getPos().y()),
        static_cast<uint8_t>(cell->getPos().x())
    };

    auto allMoves = _game->getPossibleMoves();
    if (allMoves.find(cellPos) == allMoves.end()) {
        QMessageBox msgBox;
        msgBox.setText("No Possible Move");
        msgBox.exec();
        return;
    }
    auto moves = allMoves.at(cellPos);

    PopupSelection* a = new PopupSelection(moves);
    connect(a, &PopupSelection::selectedNumber, [cell, cellPos, this](QString s){
        cell->setText(s);
        this->_game->unsafePlay(cellPos, static_cast<uint8_t>(s.toInt()));
        this->_gameString = this->_game->toString();
        delete this->_game;
        this->_game = new Game(this->_gameString);
    });
    a->move(QCursor::pos());
    a->show();
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