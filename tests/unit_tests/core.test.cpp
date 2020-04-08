#include "catch2/catch.hpp"
#include "utopia/core.h"
#include <vector>

using namespace utopia::core;
constexpr char const* TAG = "[core]";

TEST_CASE("converting utf8 to utf32 works", TAG) {
  std::string str = "Hello";
  auto buffer = utf8ToUtf32<std::string, std::vector<uint32_t>>(str);
  REQUIRE(buffer == std::vector<uint32_t>{ 0x48, 0x65, 0x6c, 0x6c, 0x6f});
}
