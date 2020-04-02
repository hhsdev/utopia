#ifndef UTOPIA_BUFFER_H
#define UTOPIA_BUFFER_H
#include "utopia/unicode_buffer_interface.h"

namespace utopia {

class SimpleUnicodeBuffer : public UnicodeBufferInterface<SimpleUnicodeBuffer> {
 public:
  SimpleUnicodeBuffer() = default;
  SimpleUnicodeBuffer(size_t size) : mBuffer(new uint32_t[size]()), mSize(size) {}

  uint32_t get(size_t) const { return 0; }
  void set(size_t, uint32_t) {}
	
	size_t size() const { return mSize; }
 private:
  uint32_t* mBuffer;
	size_t mSize;
};
}  // namespace utopia
#endif
