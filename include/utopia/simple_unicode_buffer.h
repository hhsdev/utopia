#ifndef UTOPIA_BUFFER_H
#define UTOPIA_BUFFER_H
#include <memory>
#include "utopia/index_wrapper.h"
#include "utopia/unicode_buffer_interface.h"

namespace utopia {
/**
 * Plain old vector-like buffer.
 */
class SimpleUnicodeBuffer : public UnicodeBufferInterface<SimpleUnicodeBuffer> {
  using AllocatorTraits = std::allocator_traits<std::allocator<uint32_t>>;

 public:
  SimpleUnicodeBuffer();
  SimpleUnicodeBuffer(size_t size);
  SimpleUnicodeBuffer(std::initializer_list<uint32_t> iniList);

  uint32_t operator[](size_t index) const;
  IndexWrapper<SimpleUnicodeBuffer> operator[](size_t index);
  
  void remove(size_t index) const noexcept;

  uint32_t get(size_t index) const noexcept;
  void set(size_t index, uint32_t value) noexcept;

  constexpr size_t size() const { return mSize; }

  void push_back(const uint32_t value);
  void pop_back();

  ~SimpleUnicodeBuffer();

 private:
  std::allocator<uint32_t> mAllocator;
  uint32_t* mBuffer;
  size_t mCapacity;
  size_t mSize;
};
}  // namespace utopia
#endif
