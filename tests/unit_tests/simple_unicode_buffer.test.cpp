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

TEST_CASE("push_back works", TAG) {
  SimpleUnicodeBuffer buffer;

  for (unsigned i = 0; i < 100; ++i) {
    buffer.push_back(i);
  }

  for (unsigned i = 0; i < 100; ++i) {
    REQUIRE(buffer[i] == i);
  }
}

#ifdef CATCH_CONFIG_ENABLE_BENCHMARKING

void pushBack() {
  SimpleUnicodeBuffer buffer;
  for (unsigned i = 0; i < 1000; ++i) {
    buffer.push_back(i);
  }
}

TEST_CASE("Benchmarking", TAG) {
  SimpleUnicodeBuffer buffer1, buffer2;
  BENCHMARK("push_back") { return pushBack(); };
}
#endif
