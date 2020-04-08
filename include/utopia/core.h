#ifndef UTOPIA_CORE_H
#define UTOPIA_CORE_H
#include <cstdint>
#include <string>
#include "utopia/bits.h"
#include "utopia/simple_unicode_buffer.h"

namespace utopia {
namespace core {

template <typename InputBuffer = std::string,
          typename OutputBuffer = SimpleUnicodeBuffer>
OutputBuffer utf8ToUtf32(const InputBuffer& input) {
  using namespace utopia::bits;
  uint32_t codePoint = 0U;
  OutputBuffer output;
  for (unsigned i = 0; i < input.size(); ++i) {
    uint8_t ch = static_cast<uint8_t>(input[i]);
    if (bits::isLeadingByte(ch)) {
      auto n = bits::numCodeBitsInLeadingByte(ch);

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
