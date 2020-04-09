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
  const auto sz = input.size();
  if (sz == 0)
    return OutputBuffer{};

  using namespace utopia::bits;
  OutputBuffer output;

  std::size_t endIndex = 0;
  for (unsigned i = 0; i < input.size(); ++i) {
    uint8_t ch = static_cast<uint8_t>(input[i]);
    if (isLeadingByte(ch)) {
      output.push_back(0U);
      endIndex = output.size() - 1;
      auto n = numCodeBitsInLeadingByte(ch);
      output[endIndex] = bits::pack(output[endIndex], ch, n);
    } else {
      output[endIndex] = bits::pack(output[endIndex], ch, 6);
    }
  }
  return output;
}

}  // namespace core
}  // namespace utopia
#endif
