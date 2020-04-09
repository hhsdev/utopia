#include "catch2/catch.hpp"
#include "utopia/bits.h"
#include <iostream>
using namespace utopia::bits;
constexpr char const* TAG = "[bit]";

TEST_CASE("countLeadingOnes works", TAG) {
  REQUIRE(countLeadingOnes<uint8_t>(0b1110'0000U) == 3U);
  REQUIRE(countLeadingOnes<uint8_t>(0b1110'1111U) == 3U);

  REQUIRE(countLeadingOnes<uint16_t>(0b1110'0000'0000'0000U) == 3U);
  REQUIRE(countLeadingOnes<uint16_t>(0b1110'1111'0000'0000U) == 3U);

  REQUIRE(countLeadingOnes(0b1110'0000'0000'0000'0000'0000'0000'0000U) == 3U);
  REQUIRE(countLeadingOnes(0b1110'1111'0000'0000'0000'0000'0000'0000U) == 3U);

  REQUIRE(countLeadingOnes<uint8_t>(0b0111'1111) == 0U);
}

TEST_CASE("countLeadingZeroes works", TAG) {
  REQUIRE(countLeadingZeroes<uint8_t>(0b0001'1111U) == 3U);
  REQUIRE(countLeadingZeroes<uint8_t>(0b0001'0000U) == 3U);

  REQUIRE(countLeadingZeroes<uint16_t>(0b0001'1111'1111'1111U) == 3U);
  REQUIRE(countLeadingZeroes<uint16_t>(0b0001'0000'0000'0000U) == 3U);

  REQUIRE(countLeadingZeroes(0b0001'1111'1111'1111'1111'1111'1111'1111U) == 3U);
  REQUIRE(countLeadingZeroes(0b0001'0000'0000'0000'0000'0000'0000'0000U) == 3U);

  REQUIRE(countLeadingZeroes<uint32_t>(0b0) == 32U);
  REQUIRE(countLeadingZeroes<uint8_t>(0b1000'0000) == 0U);
}
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
