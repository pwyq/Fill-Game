#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// Qt includes
#include <QMainWindow>
// #include <qt5/QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QTextBrowser>


namespace GUI
{


class MainWindow: public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(const std::string& title, const std::string& htmlPath);
        ~MainWindow();
        void initUI(const std::string& title, const std::string& htmlPath);
        void setWindowSize(const float& widthRatio, const float& heightRatio);
    protected:
        QGridLayout* layout_;
        QWidget* widget_;
        QTextBrowser *browser_;
};


} // namespace GUI


#endif