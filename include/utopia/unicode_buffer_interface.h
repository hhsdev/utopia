#ifndef UTOPIA_BUFFER_INTERFACE_H
#define UTOPIA_BUFFER_INTERFACE_H

#include "hhs/has_member_function.h"

namespace utopia {
// This is a compile-time interface. It's actually just a bunch of
// static_assert checks to whether a implementation class has all the methods
// required by the interface.
template <typename UnicodeBufferImpl>
class UnicodeBufferInterface {
  GENERATE_FUNCTION_PRESENCE_TEST(has_get, get, uint32_t(size_t))
  GENERATE_FUNCTION_PRESENCE_TEST(has_set, set, void(size_t, uint32_t))
	GENERATE_FUNCTION_PRESENCE_TEST(has_operator, operator[], uint32_t(size_t))

 public:
  UnicodeBufferInterface() {
    static_assert(has_get<UnicodeBufferImpl>::value,
                  "UnicodeBuffer Implementations must implement method "
                  "`uint32_t get(size_t)`");

    static_assert(has_set<UnicodeBufferImpl>::value,
                  "UnicodeBuffer Implementations must implement method "
                  "`uint32_t set(size_t, uint32_t)`");

		//TODO: think about whether to add checks for mutable index operators
    static_assert(
        has_operator<const UnicodeBufferImpl>::value,
        "UnicodeBuffer Implementations must implement index operators");
  }
};

}  // namespace utopia
#endif
