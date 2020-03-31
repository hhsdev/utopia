#ifndef UTOPIA_USTRING_H
#define UTOPIA_USTRING_H

#include <cstdint>

namespace utopia {
/**
 * Most versatile string type for handling utf-8 strings.
 * O(1) complexity for index operations. Use this string unless
 * you have a good reason to use other strings.
 */
class UString {
	public:

	private:
		Buffer<uint32_t, 2> mBuffer;
};
}


#endif
