#ifndef UTOPIA_UTF_32_STRING_H
#define UTOPIA_UTF_32_STRING_H

#include <cstdint>
#include <string>
#include "simple_unicode_buffer.h"
namespace utopia {
/**
 * Most versatile string type for handling utf-8 strings.
 * O(1) time complexity for index operations. Should be your goto
 * string in this library.
 */
class Utf32String {
 public:
  using Buffer = UnicodeBufferInterface<SimpleUnicodeBuffer>;
  UnicodeString() = default;
  UnicodeString(const std::string& str);

  std::size_t size() const { return mBuffer->size(); }

 private:
  Buffer mBuffer;
};

}  // namespace utopia

#endif
