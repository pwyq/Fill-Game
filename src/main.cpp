#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

#include "gui/main_window.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);                // need this; otherwise tooltip format is disgusting
    app.setFont(font);

    QCoreApplication::setApplicationName("Fill Game");

    GUI::MainWindow mainWindow;
    QScreen* screen = QGuiApplication::screenAt(QCursor::pos());
    mainWindow.move(screen->availableGeometry().center() - mainWindow.frameGeometry().center());
    mainWindow.show();

    return app.exec();
}