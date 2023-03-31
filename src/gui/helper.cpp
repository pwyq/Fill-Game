/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:31:58
 * @modify date 2023-03-31 16:38:46
 */
// local
#include "gui/helper.h"

namespace gui::helper {

bool randomBool() {
  static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
  return gen();
}

}  // namespace gui::helper
