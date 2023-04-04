/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-04-04 02:23:38
 * @modify date 2023-04-04 02:23:38
 * @desc Helper for test suite
 */

#ifndef FG_TEST_HELPER_H_
#define FG_TEST_HELPER_H_

// std
#include <stdio.h>

#include <string>

namespace fgtest::helper {

static constexpr uint32_t hash(const std::string_view data) noexcept {
  uint32_t hash = 5385;
  for (const auto& e : data) hash = ((hash << 5) + hash) + e;
  return hash;
}

}  // namespace fgtest::helper

#endif