#include "catch2/catch.hpp"
#include "utopia/simple_unicode_buffer.h"

using namespace utopia;

TEST_CASE("Constructors work", "[SimpleBuffer]") {
	SimpleUnicodeBuffer buffer(10);
	REQUIRE(buffer.size() == 10);
}
