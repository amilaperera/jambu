#pragma once
namespace jambu {
namespace detail {

// A class which expects to be a singleton
// should derive from the singleton class
template <typename Derived>
class singleton {
 public:
  singleton(const singleton&) = delete;
  singleton& operator=(const singleton&) = delete;
  static Derived& instance() {
    static Derived the_instance;
    return the_instance;
  }

 protected:
  singleton() = default;
  ~singleton() = default;
};
}  // namespace detail
}  // namespace jambu