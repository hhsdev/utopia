#ifndef UTOPIA_BUFFER_H
#define UTOPIA_BUFFER_H
#include <memory>
#include <type_traits>
#include "hhs/has_member_function.h"
#include "utopia/index_wrapper.h"
#include "utopia/unicode_buffer_interface.h"

namespace utopia {
/**
 * Plain old vector-like buffer.
 */
class SimpleUnicodeBuffer : public UnicodeBufferInterface<SimpleUnicodeBuffer> {
  using AllocatorTraits = std::allocator_traits<std::allocator<uint32_t>>;
 public:
  SimpleUnicodeBuffer() : mBuffer(nullptr), mCapacity(0), mSize(0) {}

  SimpleUnicodeBuffer(size_t size) : SimpleUnicodeBuffer() {
    mBuffer = AllocatorTraits::allocate(mAllocator, size);
    AllocatorTraits::construct(mAllocator, mBuffer);
    mSize = mCapacity = size;
  }

  uint32_t operator[](size_t index) const {
    if (index >= mSize) {
      throw std::out_of_range("Index out of range");
    }
    return mBuffer[index];
  }

  auto operator[](size_t index) {
    if (index >= mSize) {
      throw std::out_of_range("Index out of range");
    }
    return IndexWrapper<SimpleUnicodeBuffer>(*this, index);
  }

  uint32_t get(size_t index) const noexcept {
    return mBuffer[index];
  }

  void set(size_t index, uint32_t value) noexcept {
    mBuffer[index] = value;
  }

  size_t size() const { return mSize; }

  void push_back(const uint32_t value) {
    if (mSize == mCapacity) {
      if (!mCapacity) ++mCapacity;
      mCapacity *= 2;
      auto newBuffer = AllocatorTraits::allocate(mAllocator, mCapacity);
      for (unsigned i = 0; i < mSize; ++i) {
        AllocatorTraits::construct(mAllocator, newBuffer + i, *(mBuffer + i));
      }
      mBuffer = newBuffer;
    }
    AllocatorTraits::construct(mAllocator, mBuffer + mSize, value);
    ++mSize;
  }
  
  void pop_back(const uint32_t value) {
    // TODO: give back memory
    --mSize;
  }

  ~SimpleUnicodeBuffer() {
    AllocatorTraits::destroy(mAllocator, mBuffer);
    AllocatorTraits::deallocate(mAllocator, mBuffer, mCapacity);
  }
 private:
  std::allocator<uint32_t> mAllocator;
  uint32_t* mBuffer;
  size_t mCapacity;
  size_t mSize;
};
}  // namespace utopia
#endif
