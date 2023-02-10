#ifndef FG_GUI_HELPER_H_
#define FG_GUI_HELPER_H_

#include <QString>

namespace GUI {

QString uint8ToQstring(uint8_t x);

uint8_t QStringToUint8(QString s);

} // namespace GUI

#endif // FG_GUI_HELPER_H_