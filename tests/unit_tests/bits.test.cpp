#include "catch2/catch.hpp"
#include "utopia/bits.h"

using namespace utopia::bits;
constexpr char const* TAG = "[bit]";

TEST_CASE("pack works", TAG) {
  uint32_t buffer = 0U;

  SECTION("simple case", TAG) {
    buffer = pack(buffer, 0b111U, 3);
    buffer = pack(buffer, 0b1111'1100U, 2);
    buffer = pack(buffer, 0b1111'1111U, 3);

    REQUIRE(buffer == 0b11100111U);
  }
  
  SECTION("multiple types") {
    buffer = pack(buffer, static_cast<uint8_t>(0b111U), 3);
    CHECK(buffer == 0b111U);
    buffer = pack(buffer, static_cast<uint16_t>(0b1111'1100U), 2);
    CHECK(buffer == 0b11100U);
    buffer = pack(buffer, 0b1111'1111U, 3);
    REQUIRE(buffer == 0b11100111U);
  }
}
