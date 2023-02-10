/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:35:47
 * @modify date 2023-02-10 05:35:47
 * @desc main entry point of the program
 */
// Qt
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
// local
#include "gui/main_window.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QFont font("Courier New");
  font.setStyleHint(
      QFont::Monospace);  // need this; otherwise tooltip format is disgusting
  app.setFont(font);

  QCoreApplication::setApplicationName("Fill Game");

  GUI::MainWindow mainWindow;
  QScreen *screen = QGuiApplication::screenAt(QCursor::pos());
  mainWindow.move(screen->availableGeometry().center() -
                  mainWindow.frameGeometry().center());
  mainWindow.show();

  return app.exec();
}