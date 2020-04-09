#include <vector>
#include "catch2/catch.hpp"
#include "utopia/convert.h"

using namespace utopia::convert;
constexpr char const* TAG = "[convert]";

TEST_CASE("converting utf8 to utf32 works", TAG) {
  std::string str = "Hello";
  auto buffer = utf8ToUtf32<std::string, std::vector<uint32_t>>(str);
  REQUIRE(buffer == std::vector<uint32_t>{0x48, 0x65, 0x6c, 0x6c, 0x6f});

  std::string runePoem = "ᚠᛇᚻ᛫ᛒᛦᚦ᛫ᚠᚱᚩᚠᚢᚱ᛫ᚠᛁᚱᚪ᛫ᚷᛖᚻᚹᛦᛚᚳᚢᛗ";
  buffer = utf8ToUtf32<std::string, std::vector<uint32_t>>(runePoem);
  REQUIRE(buffer == std::vector<uint32_t>{5792, 5831, 5819, 5867, 5842, 5862,
                                          5798, 5867, 5792, 5809, 5801, 5792,
                                          5794, 5809, 5867, 5792, 5825, 5809,
                                          5802, 5867, 5815, 5846, 5819, 5817,
                                          5862, 5850, 5811, 5794, 5847});
}
