/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:26:24
 * @modify date 2023-03-31 19:31:04
 * @desc GUI helpers
 */
#ifndef FG_GUI_HELPER_H_
#define FG_GUI_HELPER_H_
// std
#include <random>
// Qt
#include <QMessageBox>
#include <QString>

namespace gui::helper {

///////////////////////////////////////
//  ENUM
///////////////////////////////////////
enum SOLVER {
  HUMAN_LOCAL = 0,
  HUMAN_REMOTE,  // need to optimize
  DFPN,
  PNS,
  MINIMAX_AB_TT,
  NEGAMAX_AB_TT
};

///////////////////////////////////////
// inline function declarations
///////////////////////////////////////

inline QString uint8ToQstring(uint8_t x) { return QString::number(x); }

inline uint8_t QStringToUint8(QString s) {
  return static_cast<uint8_t>(s.toInt());
}

inline void displayMessage(QString s) {
  QMessageBox msgBox;
  msgBox.setText(s);
  msgBox.exec();
}

///////////////////////////////////////
// others
///////////////////////////////////////

bool randomBool();
uint8_t getBoardCellSize(uint8_t width, uint8_t height);  // TODO: dynamic size

}  // namespace gui::helper

#endif  // FG_GUI_HELPER_H_