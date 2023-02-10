#include "gui/helper.h"

namespace GUI {

QString uint8ToQstring(uint8_t x) { return QString::number(x); }

uint8_t QStringToUint8(QString s) { return static_cast<uint8_t>(s.toInt()); }

} // namespace GUI
