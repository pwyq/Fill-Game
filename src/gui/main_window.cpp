// Qt
#include <QMessageBox>

// own include
#include "gui/main_window.h"
#include "gui/popup_selection.h"
#include "gui/helper.h"


namespace GUI
{


MainWindow::MainWindow():
    _boardWidth(5),
    _boardHeight(5)
{
    // TODO: cell color

    // UI elements
    _mainLayout     = new QHBoxLayout();
    _boardLayout    = new QGridLayout();
    _infoLayout     = new QGridLayout();
    _mainWidget     = new QWidget();
    _currPlayer     = new QLabel();
    _browser        = new QTextBrowser();

    // Solver elements
    this->startNewGame();

    // UI related
    _gameMenu  = this->menuBar()->addMenu("&Game");
    _boardMenu = this->menuBar()->addMenu("&Board");
    this->initUI();
    this->setAttribute( Qt::WA_DeleteOnClose );
}

MainWindow::~MainWindow()
{
    delete _boardLayout;
    delete _infoLayout;
    delete _mainLayout;
    delete _mainWidget;
    for (auto p : _boardVec) {
        delete p;
    }
    _boardVec.clear();
}

void MainWindow::initUI()
{
    this->setWindowTitle(QString::fromStdString("Fill Game"));
    this->initGameMenu();
    this->initBoardMenu(); 


    this->drawBoard();
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

void MainWindow::initGameMenu()
{
    QAction* startNewGame = new QAction("Start &New Game", _gameMenu);
    connect(startNewGame, &QAction::triggered, [this](){
        this->startNewGame();
    });
    _gameMenu->addAction(startNewGame);

    _gameMenu->addSeparator();

    QAction* quit = new QAction("&Quit", _gameMenu);
    connect(quit, &QAction::triggered, [this](){
        this->close();
    });
    _gameMenu->addAction(quit);
}

void MainWindow::initBoardMenu()
{
    QAction* three = new QAction("3 x 3", _boardMenu);
    connect(three, &QAction::triggered, [this]() {
        this->changeGameSize(3, 3);
    });
    _boardMenu->addAction(three);

    QAction* five  = new QAction("5 x 5", _boardMenu);
    connect(five, &QAction::triggered, [this]() {
        this->changeGameSize(5, 5);
    });
    _boardMenu->addAction(five);

    QAction* seven = new QAction("7 x 7", _boardMenu);
    connect(seven, &QAction::triggered, [this]() {
        this->changeGameSize(7, 7);
    });
    _boardMenu->addAction(seven);

    QAction* ten   = new QAction("10 x 10", _boardMenu);
    connect(ten, &QAction::triggered, [this]() {
        this->changeGameSize(10, 10);
    });
    _boardMenu->addAction(ten);
    /*
    QAction* custom = new QAction("&Custom Board Size", _boardMenu);
    connect(ten, &QAction::triggered, [this]() {
        QStringList list = InputDialog::getStrings(this);
        if (!list.isEmpty()) {
            // use list
        }
        emit this->changeGameSize(10, 10);
    });
    _boardMenu->addAction(custom);
    */
}

void MainWindow::startNewGame()
{
    std::string _gameString = "";
    for (uint8_t row = 0; row < _boardHeight; row++) {
        for (uint8_t col = 0; col < _boardWidth; col++) {
            _gameString += ".";
        }
        _gameString += "*";
    }
    _gameString.pop_back();

    if (_game != nullptr) {
        _game = nullptr;
        delete _game;
    }
    _game = new Solver::Game(_gameString);

    // clear UI
    for (auto c : _boardVec) {
        c->setEnabled(true);
        c->setText("");
    }
    this->updateCurrentPlayer(this->_game->to_play);
    _browser->clear();
}

void MainWindow::changeGameSize(uint8_t width, uint8_t height)
{
    _boardHeight = height;
    _boardWidth  = width;
    std::string _gameString = "";
    for (uint8_t row = 0; row < _boardHeight; row++) {
        for (uint8_t col = 0; col < _boardWidth; col++) {
            _gameString += ".";
        }
        _gameString += "*";
    }
    _gameString.pop_back();

    if (_game != nullptr) {
        _game = nullptr;
        delete _game;
    }
    _game = new Solver::Game(_gameString);

    // redraw & clear UI
    this->clearBoardLayout();
    _boardVec.clear();
    this->drawBoard();
    this->updateCurrentPlayer(this->_game->to_play);
    _browser->clear();
}

// TODO: How to make a type T*& becomes T*?? 
// template<class T>
// void MainWindow::clearLayout(T* layout, bool deleteWidgets = true)
// void MainWindow::clearLayout(QGridLayout* layout, bool deleteWidgets = true)
void MainWindow::clearBoardLayout()
{
    while (_boardLayout->count() > 0) {
        auto item = _boardLayout->itemAt(0)->widget();
        item->deleteLater();
        delete item;
    }
}

void MainWindow::drawBoard()
{
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
            // user clicked a dead cell
            a->close();
            for (auto c : this->_boardVec) {
                c->setEnabled(false);
            }
            QMessageBox msgBox;
            msgBox.setText("Winner: " + this->_currPlayer->text());
            msgBox.exec();
        } else {
            // the move was successful
            cell->setEnabled(false);
            this->_browser->append(this->getMoveMessage(cellPos, moveValue));
            this->updateCurrentPlayer(this->_game->to_play);
            a->close();
        }
    });
    a->move(QCursor::pos());
    a->show();
}


} // namespace GUI