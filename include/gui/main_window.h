#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// Qt includes
#include <QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
// #include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QMenuBar>
#include <QMenu>
#include <QDebug>

#include <iostream>
#include <vector>

#include "gui/board_cell.h"
#include "gui/input_dialog.h"
#include "solver/game.h"


namespace GUI
{

// TODO: singleton
class MainWindow: public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow();
        ~MainWindow();
        void initUI();
        void startNewGame();
        void changeGameSize(uint8_t width, uint8_t height);
    protected:
        QHBoxLayout*    _mainLayout;
        QGridLayout*    _boardLayout;
        QGridLayout*    _infoLayout;
        QWidget*        _mainWidget;
        QLabel*         _currPlayer;
        QTextBrowser*   _browser;

        QMenu* _gameMenu;
        QMenu* _boardMenu;
        uint8_t _boardWidth;
        uint8_t _boardHeight;
        std::vector<BoardCell*> _boardVec;

        void initGameMenu();
        void initBoardMenu();
        void drawBoard();
        void updateCurrentPlayer(Solver::PLAYER player);
        QString getMoveMessage(Solver::Pos pos, QString moveValue);

        // slots
        void onBoardCellPressed(BoardCell* cell);
    private:
        // template<class T>
        // void clearLayout(T* layoutType, bool deleteWidgets);
        void clearBoardLayout();
        Solver::Game* _game = nullptr;    // TODO: std::auto_ptr, std::shared_ptr?
        std::string _gameString;
        int _moveCounter = 1;
};


} // namespace GUI


#endif