#include <iostream>
namespace jambu {
namespace detail {
struct null_mutex {
  void lock() {}
  void unlock() {}
};
}
}  // namespace jambu