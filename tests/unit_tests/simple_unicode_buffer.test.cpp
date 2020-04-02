#include "catch2/catch.hpp"
#include "utopia/simple_unicode_buffer.h"

using namespace utopia;

TEST_CASE("Constructors work", "[SimpleUnicodeBuffer]") {
	SimpleUnicodeBuffer buffer(10);
	REQUIRE(buffer.size() == 10);
}


TEST_CASE("set and get work", "[SimpleUnicodeBuffer]") {
	SimpleUnicodeBuffer buffer(1);
	buffer.set(0, 0xdeadbeef);

	REQUIRE(buffer.get(0) == 0xdeadbeef);
}
