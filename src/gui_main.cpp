/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:35:47
 * @modify date 2023-03-15 10:28:46
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
  app.setWindowIcon(QIcon(":/resource/icons/fill_game_logo.ico"));

  QCoreApplication::setApplicationName("Fill Game");

  gui::MainWindow mainWindow;
  QScreen *screen = QGuiApplication::screenAt(QCursor::pos());
  mainWindow.move(screen->availableGeometry().center() -
                  mainWindow.frameGeometry().center());
  mainWindow.show();

  return app.exec();
}