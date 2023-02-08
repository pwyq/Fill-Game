#include <QApplication>
#include <QDesktopWidget>

#include "gui/main_window.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);                // need this; otherwise tooltip format is disgusting
    app.setFont(font);

    QCoreApplication::setApplicationName("Fill Game");

    GUI::MainWindow mainWindow;
    mainWindow.move(QApplication::desktop()->screen()->rect().center() - mainWindow.frameGeometry().center());
    mainWindow.show();

    return app.exec();
}