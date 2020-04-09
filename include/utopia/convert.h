#ifndef UTOPIA_CORE_H
#define UTOPIA_CORE_H
#include <cstdint>
#include <string>
#include "utopia/bits.h"
#include "utopia/simple_unicode_buffer.h"
#include "utopia/utf_8.h"

namespace utopia {
namespace convert {

template <typename InputBuffer = std::string,
          typename OutputBuffer = SimpleUnicodeBuffer>
OutputBuffer utf8ToUtf32(const InputBuffer& input);

}  // namespace convert
}  // namespace utopia

namespace utopia {
namespace convert {

template <typename InputBuffer = std::string,
          typename OutputBuffer = SimpleUnicodeBuffer>
OutputBuffer utf8ToUtf32(const InputBuffer& input) {
  const auto sz = input.size();
  if (sz == 0)
    return OutputBuffer{};

  using namespace utopia::bits;
  using namespace utopia::utf8;
  OutputBuffer output;

  std::size_t endIndex = 0;
  for (unsigned i = 0; i < input.size(); ++i) {
    uint8_t ch = static_cast<uint8_t>(input[i]);
    if (utf8::isLeadingByte(ch)) {
      output.push_back(0U);
      endIndex = output.size() - 1;
      auto n = utf8::numCodeBitsInLeadingByte(ch);
      output[endIndex] = bits::pack(output[endIndex], ch, n);
    } else {
      output[endIndex] = bits::pack(output[endIndex], ch, 6);
    }
  }
  return output;
}

}  // namespace convert
}  // namespace utopia
#endif
