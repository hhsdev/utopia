#include "catch2/catch.hpp"
#include "utopia/simple_unicode_buffer.h"

using namespace utopia;
constexpr char const* TAG = "[SimpleUnicodeBuffer]";

SimpleUnicodeBuffer constructWithPushBack(size_t size) {
  SimpleUnicodeBuffer buffer;
  for (unsigned i = 0; i < size; ++i) {
    buffer.push_back(i);
  }
  return buffer;
}

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
  SimpleUnicodeBuffer buffer = constructWithPushBack(100);

  for (unsigned i = 0; i < 100; ++i) {
    REQUIRE(buffer[i] == i);
  }
}

TEST_CASE("pop_back works", TAG) {
  SimpleUnicodeBuffer buffer = constructWithPushBack(100);

  auto size = buffer.size();
  for (unsigned i = 0; i < 100; ++i) {
    buffer.pop_back();
    --size;
    REQUIRE(buffer.size() == size);
  }
}

TEST_CASE("remove works", TAG) {
  SimpleUnicodeBuffer buffer = constructWithPushBack(10);

  buffer.remove(2);
  REQUIRE(buffer.size() == 9);
  REQUIRE(buffer[0] == 0);
  REQUIRE(buffer[1] == 1);
  REQUIRE(buffer[2] == 3);
  REQUIRE(buffer[3] == 4);

  buffer.remove(0);
  REQUIRE(buffer.size() == 8);
  REQUIRE(buffer[0] == 1);
  REQUIRE(buffer[1] == 3);
  REQUIRE(buffer[2] == 4);
}

TEST_CASE("Insert works", TAG) {
  SimpleUnicodeBuffer buffer = constructWithPushBack(5);

  buffer.insert(1, 0xdeadbeef);
  REQUIRE(buffer[0] == 0);
  REQUIRE(buffer[1] == 0xdeadbeef);
  REQUIRE(buffer[2] == 1);

  buffer.insert(0, 0xcafebabe);
  REQUIRE(buffer[0] == 0xcafebabe);
  REQUIRE(buffer[1] == 0);
  REQUIRE(buffer[2] == 0xdeadbeef);
  REQUIRE(buffer[3] == 1);
}
#ifdef CATCH_CONFIG_ENABLE_BENCHMARKING

TEST_CASE("Benchmarking", TAG) {
  BENCHMARK("push_back") { return constructWithPushBack(1000); };
}
#endif
