#include <QApplication>
#include "gui/main_window.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI::MainWindow w("123", "456");
    w.show();

    return a.exec();
}