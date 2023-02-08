#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// Qt includes
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMenuBar>

// #include <iostream>
#include <vector>

#include "gui/board_cell.h"
#include "solver/game.h"


namespace GUI
{


class MainWindow: public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow();
        ~MainWindow();
        void initUI();
        void setWindowSize(const float& widthRatio, const float& heightRatio);
    protected:
        QGridLayout* _layout;
        QWidget* _widget;
        QMenuBar* _menuBar;
        
        uint8_t _boardWidth;
        uint8_t _boardHeight;
        std::vector<BoardCell*> _boardVec;

        void onBoardCellPressed(BoardCell* cell);
    private:
        Game* _game;    // TODO: std::auto_ptr, std::shared_ptr
        std::string _gameString;
};


} // namespace GUI


#endif