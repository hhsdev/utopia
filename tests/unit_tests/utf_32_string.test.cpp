#include "catch.hpp"
#include "utopia/utf_32_string.hpp"

constexpr char const* TAG = "[Utf32String]";

TEST_CASE("Construction works", TAG) {
  std::string str = "Hello World!";
  UnicodeString ustring(str);
  REQUIRE(ustring.size() == str.size());
}
