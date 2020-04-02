#ifndef UTOPIA_USTRING_H
#define UTOPIA_USTRING_H

#include <cstdint>

namespace utopia {
/**
 * Most versatile string type for handling utf-8 strings.
 * O(1) time complexity for index operations. Should be your goto
 * string in this library.
 */
class UString {

public:
private:
	uint8_t charSize;
  Buffer<uint32_t, 2> mBuffer;

};

} // namespace utopia

#endif
