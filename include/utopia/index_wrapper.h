#ifndef UTOPIA_INDEX_WRAPPER_H
#define UTOPIA_INDEX_WRAPPER_H
namespace utopia {
template <typename Container>
class IndexWrapper {
  GENERATE_FUNCTION_PRESENCE_TEST(has_get, get, uint32_t(size_t))
  GENERATE_FUNCTION_PRESENCE_TEST(has_set, set, void(size_t, uint32_t))
 public:
  using Element =
      decltype(std::declval<Container>().get(std::declval<size_t>()));
  IndexWrapper(Container& container, size_t index)
      : mContainer(&container), mIndex(index) {
    static_assert(has_get<Container>::value,
                  "Container must implement method `uint32_t get(size_t)`");
    static_assert(
        has_set<Container>::value,
        "Container must implement method `uint32_t set(size_t, uint32_t)`");
  }

  IndexWrapper& operator=(const Element& value) {
    mContainer->set(mIndex, value);
    return *this;
  }

  operator Element() const { return mContainer->get(mIndex); }

 private:
  Container* mContainer = nullptr;
  size_t mIndex = 0;
};
}  // namespace utopia

#endif
