#ifndef UTOPIA_BUFFER_H
#define UTOPIA_BUFFER_H
#include "utopia/unicode_buffer_interface.h"
#include "utopia/index_wrapper.h"
#include <memory>

namespace utopia {
/**
 * Plain old vector-like buffer.
 */
class SimpleUnicodeBuffer : public UnicodeBufferInterface<SimpleUnicodeBuffer> {
  using AllocatorTraits = std::allocator_traits<std::allocator<uint32_t>>;

 public:
  SimpleUnicodeBuffer();

  SimpleUnicodeBuffer(size_t size);

  uint32_t operator[](size_t index) const;
  IndexWrapper<SimpleUnicodeBuffer> operator[](size_t index);

  uint32_t get(size_t index) const noexcept;

  void set(size_t index, uint32_t value) noexcept;

  size_t size() const;

  void push_back(const uint32_t value);

  void pop_back(const uint32_t value);

  ~SimpleUnicodeBuffer();

 private:
  std::allocator<uint32_t> mAllocator;
  uint32_t* mBuffer;
  size_t mCapacity;
  size_t mSize;
};
}  // namespace utopia
#endif
