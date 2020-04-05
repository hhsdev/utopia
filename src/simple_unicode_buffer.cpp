#include "utopia/simple_unicode_buffer.h"
#include <cstring>
#include <type_traits>

namespace utopia {
SimpleUnicodeBuffer::SimpleUnicodeBuffer()
    : mBuffer(nullptr), mCapacity(0), mSize(0) {}

SimpleUnicodeBuffer::SimpleUnicodeBuffer(size_t size) : SimpleUnicodeBuffer() {
  mBuffer = AllocatorTraits::allocate(mAllocator, size);
  AllocatorTraits::construct(mAllocator, mBuffer);
  mSize = mCapacity = size;
}

SimpleUnicodeBuffer::SimpleUnicodeBuffer(
    std::initializer_list<uint32_t> iniList) {
  mBuffer = AllocatorTraits::allocate(mAllocator, iniList.size());
  std::uninitialized_copy(std::begin(iniList), std::end(iniList), mBuffer);
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

void SimpleUnicodeBuffer::push_back(const uint32_t value) {
  if (mSize == mCapacity) {
    if (mCapacity == 0) mCapacity = 1;
    mCapacity *= 2;
    auto newBuffer = AllocatorTraits::allocate(mAllocator, mCapacity);
    std::uninitialized_copy(mBuffer, mBuffer + mSize, newBuffer);
    mBuffer = newBuffer;
  }
  AllocatorTraits::construct(mAllocator, mBuffer + mSize, value);
  ++mSize;
}

void SimpleUnicodeBuffer::pop_back() {
  AllocatorTraits::destroy(mAllocator, mBuffer + mSize - 1);
  --mSize;
}

SimpleUnicodeBuffer::~SimpleUnicodeBuffer() {
  AllocatorTraits::destroy(mAllocator, mBuffer);
  AllocatorTraits::deallocate(mAllocator, mBuffer, mCapacity);
}

void SimpleUnicodeBuffer::remove(size_t index) const noexcept {
  auto ptrToRemove = mBuffer + index;
  std::copy(ptrToRemove + 1, mBuffer + size, ptrToRemove);
  this->pop_back();
}

}  // namespace utopia
