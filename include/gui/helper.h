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

namespace GUI {

QString uint8ToQstring(uint8_t x);

uint8_t QStringToUint8(QString s);

}  // namespace GUI

#endif  // FG_GUI_HELPER_H_