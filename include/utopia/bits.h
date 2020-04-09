#ifndef UTOPIA_BITS_H
#define UTOPIA_BITS_H
#include <climits>
#include <iostream>
#include <type_traits>

namespace utopia {
// Synopsis
namespace bits {
template <typename Unsigned>
std::string toBinary(Unsigned bits);

template <typename Unsigned>
inline typename std::enable_if<std::is_unsigned_v<Unsigned>, unsigned>::type
countLeadingOnes(Unsigned bits);

template <typename Unsigned>
inline typename std::enable_if<std::is_unsigned_v<Unsigned>, unsigned>::type
countLeadingZeroes(Unsigned bits);

template <typename Buffer, typename Bits>
Buffer pack(Buffer buffer, Bits bits, uint8_t sz);

}  // namespace bits
}  // namespace utopia

namespace utopia {
// Implementation
namespace bits {

template <typename Unsigned>
std::string toBinary(Unsigned bits) {
  constexpr auto BIT_SIZE = sizeof(Unsigned) * CHAR_BIT;
  std::string ret(BIT_SIZE, '0');
  for (auto i = ret.size(); i != 0; --i) {
    if (bits & Unsigned(1))
      ret[i - 1] = '1';
    bits = static_cast<Unsigned>(bits >> 1);
  }
  return ret;
}

template <typename Unsigned>
inline typename std::enable_if<std::is_unsigned_v<Unsigned>, unsigned>::type
countLeadingOnes(Unsigned bits) {
  constexpr auto BIT_SIZE = sizeof(Unsigned) * CHAR_BIT;
  Unsigned mask = static_cast<Unsigned>(1) << (BIT_SIZE - 1);

  unsigned leadingOneCount = 0;

  while ((bits & mask) != 0) {
    ++leadingOneCount;
    mask = static_cast<Unsigned>(static_cast<Unsigned>(mask) >> 1);
  }
  return leadingOneCount;
}

template <typename Unsigned>
inline typename std::enable_if<std::is_unsigned_v<Unsigned>, unsigned>::type
countLeadingZeroes(Unsigned bits) {
  const Unsigned invertedBits = static_cast<Unsigned>(~bits);
  return countLeadingOnes<Unsigned>(invertedBits);
}

template <typename Buffer, typename Bits>
Buffer pack(Buffer buffer, Bits bits, uint8_t sz) {
  constexpr uint8_t numBitsInBits = sizeof(bits) * CHAR_BIT;
  const uint8_t leftShiftCount = static_cast<uint8_t>(numBitsInBits - sz);
  buffer <<= sz;
  const Bits mask = static_cast<Bits>(static_cast<Bits>(~0) >> leftShiftCount);
  bits &= mask;
  return buffer | bits;
}

}  // namespace bits
}  // namespace utopia
#endif
