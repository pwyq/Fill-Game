/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:26:24
 * @modify date 2023-02-10 05:26:24
 * @desc GUI helpers
 */
#ifndef FG_GUI_HELPER_H_
#define FG_GUI_HELPER_H_
// Qt
#include <QString>

namespace gui {

// inline function declarations
inline QString uint8ToQstring(uint8_t x) { return QString::number(x); }

inline uint8_t QStringToUint8(QString s) {
  return static_cast<uint8_t>(s.toInt());
}

}  // namespace gui

#endif  // FG_GUI_HELPER_H_