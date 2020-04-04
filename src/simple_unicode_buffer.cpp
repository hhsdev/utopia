#include "utopia/simple_unicode_buffer.h"
#include <type_traits>

namespace utopia {
SimpleUnicodeBuffer::SimpleUnicodeBuffer()
    : mBuffer(nullptr), mCapacity(0), mSize(0) {}

SimpleUnicodeBuffer::SimpleUnicodeBuffer(size_t size) : SimpleUnicodeBuffer() {
  mBuffer = AllocatorTraits::allocate(mAllocator, size);
  AllocatorTraits::construct(mAllocator, mBuffer);
  mSize = mCapacity = size;
}

uint32_t SimpleUnicodeBuffer::operator[](size_t index) const {
  if (index >= mSize) {
    throw std::out_of_range("Index out of range");
  }
  return mBuffer[index];
}

IndexWrapper<SimpleUnicodeBuffer> SimpleUnicodeBuffer::operator[](
    size_t index) {
  if (index >= mSize) {
    throw std::out_of_range("Index out of range");
  }
  return IndexWrapper<SimpleUnicodeBuffer>(*this, index);
}

uint32_t SimpleUnicodeBuffer::get(size_t index) const noexcept {
  return mBuffer[index];
}

void SimpleUnicodeBuffer::set(size_t index, uint32_t value) noexcept {
  mBuffer[index] = value;
}

size_t SimpleUnicodeBuffer::size() const {
  return mSize;
}

void SimpleUnicodeBuffer::push_back(const uint32_t value) {
  if (mSize == mCapacity) {
    if (!mCapacity)
      ++mCapacity;
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

void SimpleUnicodeBuffer::pop_back(const uint32_t value) {
  // TODO: give back memory
  --mSize;
}

SimpleUnicodeBuffer::~SimpleUnicodeBuffer() {
  AllocatorTraits::destroy(mAllocator, mBuffer);
  AllocatorTraits::deallocate(mAllocator, mBuffer, mCapacity);
}

}  // namespace utopia
