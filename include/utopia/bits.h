#ifndef UTOPIA_BITS_H
#define UTOPIA_BITS_H
#include <climits>
#include <iostream>

namespace utopia {
namespace bits {

template <typename Buffer, typename Bits>
Buffer pack(Buffer buffer, Bits bits, uint8_t sz) {
  constexpr uint8_t numBitsInBits = sizeof(bits) * CHAR_BIT;
  const uint8_t leftShiftCount = static_cast<uint8_t>(numBitsInBits - sz);
  buffer <<= sz;
  const Bits mask = static_cast<Bits>(static_cast<Bits>(~0) >> leftShiftCount);
  bits &= mask;
  return buffer | bits;
}

inline bool isLeadingByte(uint8_t byte) {
  return (byte >> 6) != 0b10;
}

inline uint8_t numCodeBitsInLeadingByte(uint8_t byte) {
  if ((byte & 0b1000'0000) == static_cast<uint8_t>(0))
    return 7;
  if ((byte & 0b1110'0000) == static_cast<uint8_t>(0b1100'0000))
    return 5;
  if ((byte & 0b1111'0000) == static_cast<uint8_t>(0b1110'0000))
    return 4;
  if ((byte & 0b1111'1000) == static_cast<uint8_t>(0b1111'0000))
    return 3;

  throw std::runtime_error("Should not reach here");
}

}  // namespace bits
}  // namespace utopia

#endif
