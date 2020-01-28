namespace jambu {
namespace detail {
struct null_mutex {
  void lock() {}
  void unlock() noexcept {}
};
}
}  // namespace jambu
