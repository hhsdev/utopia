#include "utopia/utf_32_string.h"
#include "utopia/core.h"

namespace utopia {

UnicodeString::UnicodeString(const std::string& str)
    : mBuffer(core::toUtf32(str)) {}

}  // namespace utopia
