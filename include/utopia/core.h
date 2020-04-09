#ifndef UTOPIA_CORE_H
#define UTOPIA_CORE_H
#include <cstdint>
#include <string>
#include "utopia/bits.h"
#include "utopia/simple_unicode_buffer.h"

namespace utopia {
namespace core {

inline bool isUtf8LeadingByte(uint8_t byte);
inline uint8_t numCodeBitsInLeadingByte(uint8_t byte);

template <typename InputBuffer = std::string,
          typename OutputBuffer = SimpleUnicodeBuffer>
OutputBuffer utf8ToUtf32(const InputBuffer& input);

}  // namespace core
}  // namespace utopia

namespace utopia {
namespace core {

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

template <typename InputBuffer = std::string,
          typename OutputBuffer = SimpleUnicodeBuffer>
OutputBuffer utf8ToUtf32(const InputBuffer& input) {
  using namespace utopia::bits;

  uint32_t codePoint = 0U;
  OutputBuffer output;

  for (unsigned i = 0; i < input.size(); ++i) {
    uint8_t ch = static_cast<uint8_t>(input[i]);
    if (isLeadingByte(ch)) {
      auto n = numCodeBitsInLeadingByte(ch);

      codePoint = bits::pack(codePoint, uint8_t(ch), n);
      output.push_back(codePoint);
      codePoint = 0U;
    } else {
      bits::pack(codePoint, uint8_t(ch & 0b0011'1111), 0);
    }
  }
  return output;
}

}  // namespace core
}  // namespace utopia
#endif
