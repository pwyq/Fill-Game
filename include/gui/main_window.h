#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// Qt includes
#include <QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QMenuBar>
#include <QLabel>

#include <iostream>
#include <vector>

#include "gui/board_cell.h"
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
        void setWindowSize(const float& widthRatio, const float& heightRatio);
    protected:
        QHBoxLayout* _mainLayout;
        QGridLayout* _boardLayout;
        QGridLayout* _infoLayout;
        QWidget* _mainWidget;
        QMenuBar* _menuBar;
        QLabel* _currPlayer;

        uint8_t _boardWidth;
        uint8_t _boardHeight;
        std::vector<BoardCell*> _boardVec;

        void updateCurrentPlayer(Solver::PLAYER);

        // slots
        void onBoardCellPressed(BoardCell* cell);
    private:
        Solver::Game* _game;    // TODO: std::auto_ptr, std::shared_ptr
        std::string _gameString;
};


} // namespace GUI


#endif