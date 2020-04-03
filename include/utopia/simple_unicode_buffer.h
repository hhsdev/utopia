#ifndef UTOPIA_BUFFER_H
#define UTOPIA_BUFFER_H
#include <type_traits>
#include "hhs/has_member_function.h"
#include "utopia/index_wrapper.h"
#include "utopia/unicode_buffer_interface.h"

namespace utopia {

class SimpleUnicodeBuffer : public UnicodeBufferInterface<SimpleUnicodeBuffer> {
 public:
  SimpleUnicodeBuffer() = default;
  SimpleUnicodeBuffer(size_t size)
      : mBuffer(new uint32_t[size]()), mSize(size) {}

  uint32_t operator[](size_t index) const { return mBuffer[index]; }

  auto operator[](size_t index) {
    return IndexWrapper<SimpleUnicodeBuffer>(*this, index);
  }
  uint32_t get(size_t index) const { return mBuffer[index]; }
  void set(size_t index, uint32_t value) { mBuffer[index] = value; }

  size_t size() const { return mSize; }

 private:
  uint32_t* mBuffer;
  size_t mSize;
};
}  // namespace utopia
#endif
