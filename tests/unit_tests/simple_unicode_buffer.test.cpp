#include "catch2/catch.hpp"
#include "utopia/simple_unicode_buffer.h"

using namespace utopia;
constexpr char const* TAG = "[SimpleUnicodeBuffer]";
TEST_CASE("constructors work", TAG) {
	SimpleUnicodeBuffer buffer(10);
	REQUIRE(buffer.size() == 10);
}

TEST_CASE("set and get work", TAG) {
	SimpleUnicodeBuffer buffer(1);
	buffer.set(0, 0xdeadbeef);

	REQUIRE(buffer.get(0) == 0xdeadbeef);
}

TEST_CASE("index operator works", TAG) {
	SimpleUnicodeBuffer buffer(5);

	buffer.set(3, 0xdeadbeef);
	REQUIRE(buffer[3] == 0xdeadbeef);

	buffer[2] = 0xcafebabe;
	REQUIRE(buffer[2] == 0xcafebabe);
}


