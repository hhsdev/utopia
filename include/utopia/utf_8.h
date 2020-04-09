#ifndef UTOPIA_UTF_8_H
#define UTOPIA_UTF_8_H
namespace utopia {
namespace utf8 {

bool isUtf8LeadingByte(uint8_t byte);
uint8_t numCodeBitsInLeadingByte(uint8_t byte);

}  // namespace utf8
}  // namespace utopia

namespace utopia {
namespace utf8 {
inline bool isLeadingByte(uint8_t byte) {
  return (byte >> 6) != 0b10;
}

inline uint8_t numCodeBitsInLeadingByte(uint8_t byte) {
  if ((byte & 0b1000'0000) == 0)
    return 7;
  if ((byte & 0b1110'0000) == 0b1100'0000)
    return 5;
  if ((byte & 0b1111'0000) == 0b1110'0000)
    return 4;
  if ((byte & 0b1111'1000) == 0b1111'0000)
    return 3;

  throw std::runtime_error("Should not reach here");
}

}  // namespace utf8
}  // namespace utopia
#endif
