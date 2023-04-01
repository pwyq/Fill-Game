/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:31:58
 * @modify date 2023-03-31 16:38:46
 */

#include "gui/helper.h"

namespace gui::helper {

bool randomBool() {
  static std::mt19937_64 gen(std::random_device{}());
  static std::uniform_int_distribution<int> dis(0, 1);
  return dis(gen) == 1;
}

}  // namespace gui::helper
