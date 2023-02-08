// Qt
#include <QMenu>
#include <QMessageBox>

// own include
#include "gui/main_window.h"
#include "gui/popup_selection.h"
#include "gui/helper.h"


namespace GUI
{


MainWindow::MainWindow()
{
    // temporary
    _boardHeight = 4;
    _boardWidth  = 4;

    // UI elements
    _mainLayout     = new QHBoxLayout();
    _boardLayout    = new QGridLayout();
    _infoLayout     = new QGridLayout();
    _mainWidget     = new QWidget();

    _menuBar        = new QMenuBar();
    _currPlayer     = new QLabel();
    _browser        = new QTextBrowser();

    // Solver elements
    std::string _gameString = "";
    for (uint8_t row = 0; row < _boardHeight; row++) {
        for (uint8_t col = 0; col < _boardWidth; col++) {
            _gameString += ".";
        }
        _gameString += "*";
    }
    _gameString.pop_back();
    _game       = new Solver::Game(_gameString);

    this->initUI();
    this->setAttribute( Qt::WA_DeleteOnClose );
}

MainWindow::~MainWindow()
{
    delete _boardLayout;
    delete _mainWidget;
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

    // init board x y axis
    for (uint8_t col = 1; col < _boardWidth+1; col++) {
        char c = 64 + col;  // ascii 'A' = 65
        QLabel* l = new QLabel(QChar(c));
        l->setAlignment(Qt::AlignCenter);
        _boardLayout->addWidget(l, 0, col, 1, 1);
    }
    for (uint8_t row = 1; row < _boardHeight+1; row++) {
        _boardLayout->addWidget(new QLabel(uint8ToQstring(row)), row, 0, 1, 1);
    }
    // init board cells
    for (uint8_t row = 0; row < _boardHeight; row++) {
        for (uint8_t col = 0; col < _boardWidth; col++) {
            QString t = "";
            BoardCell* button = new BoardCell(t, QPoint(col, row), this);   // note that col=x, row=y, from top down
            _boardVec.push_back(button);
            connect(button, &QPushButton::pressed, [button, this](){
                this->onBoardCellPressed(button);
            });
            // offset each cell because of the x-y axis labels
            _boardLayout->addWidget(button, row+1, col+1, 1, 1);
        }
    }
    // init info layout
    _infoLayout->addWidget(new QLabel("Current Player"), 0, 0, 1, 1);
    this->updateCurrentPlayer(this->_game->to_play);
    _infoLayout->addWidget(_currPlayer, 0, 1, 1, 1);
    _infoLayout->addWidget(_browser, 1, 0, 2, 2);

    _mainLayout->addLayout(_boardLayout);
    _mainLayout->addLayout(_infoLayout);
    _mainWidget->setLayout(_mainLayout);
    this->setCentralWidget(_mainWidget);
}

void MainWindow::updateCurrentPlayer(Solver::PLAYER p)
{
    if (p == Solver::PLAYER::BLACK)
        this->_currPlayer->setText("BLACK");
    else
        this->_currPlayer->setText("WHITE");
}

QString MainWindow::getMoveMessage(Solver::Pos p, QString val)
{
    QString res = QString::number(this->_moveCounter++) + ". " + this->_currPlayer->text() + ": ";
    char c = 65 + p.col;    // 'A' = 65
    res += QChar(c);
    res += uint8ToQstring(p.row+1);
    res += " - ";
    res += val;
    return res;
}

void MainWindow::onBoardCellPressed(BoardCell* cell)
{
    Solver::Pos cellPos = Solver::Pos{
        static_cast<uint8_t>(cell->getPos().y()),
        static_cast<uint8_t>(cell->getPos().x())
    };

    auto allMoves = _game->getPossibleMoves();
    if (allMoves.find(cellPos) == allMoves.end()) {
        QMessageBox msgBox;
        msgBox.setText("No Possible Move");
        msgBox.exec();
        cell->setEnabled(false);
        return;
    }
    auto moves = allMoves.at(cellPos);

    PopupSelection* a = new PopupSelection(moves);
    connect(a, &PopupSelection::selectedNumber, [cell, cellPos, a, this](QString moveValue){
        cell->setText(moveValue);
        this->_game->unsafePlay(cellPos, QStringToUint8(moveValue));
        this->_gameString = this->_game->toString();
        delete this->_game;
        this->_game = new Solver::Game(this->_gameString);

        if (this->_game->getPossibleMoves().size() == 0) {
            a->close();
            for (auto c : this->_boardVec) {
                c->setEnabled(false);
            }
            QMessageBox msgBox;
            msgBox.setText("Winner: " + this->_currPlayer->text());
            msgBox.exec();
        } else {
            this->_browser->append(this->getMoveMessage(cellPos, moveValue));
            this->updateCurrentPlayer(this->_game->to_play);
            a->close();
        }
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