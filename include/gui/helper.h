/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:26:24
 * @modify date 2023-03-23 16:23:05
 * @desc GUI helpers
 */
#ifndef FG_GUI_HELPER_H_
#define FG_GUI_HELPER_H_
// Qt
#include <QString>

namespace gui::helper {

///////////////////////////////////////
//  ENUM
///////////////////////////////////////
enum SOLVER {
  HUMAN_LOCAL = 0,
  DFPN,
  PNS,            // TODO
  MINIMAX_AB_TT,  // TODO
  NEGAMAX_AB_TT   // TODO
};

// inline function declarations
inline QString uint8ToQstring(uint8_t x) { return QString::number(x); }

inline uint8_t QStringToUint8(QString s) {
  return static_cast<uint8_t>(s.toInt());
}

}  // namespace gui::helper

#endif  // FG_GUI_HELPER_H_