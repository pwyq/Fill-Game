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

uint8_t getBoardCellSize(uint8_t width, uint8_t height) {
  // TODO: set cell size based on screen resolution
  uint8_t min_edge = (width < height) ? width : height;
  // get the minimum resolution
  return min_edge;
}

}  // namespace gui::helper
