/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:31:58
 * @modify date 2023-02-10 05:31:58
 */
// local
#include "gui/helper.h"

namespace GUI {

inline QString uint8ToQstring(uint8_t x) { return QString::number(x); }

inline uint8_t QStringToUint8(QString s) {
  return static_cast<uint8_t>(s.toInt());
}

}  // namespace GUI
