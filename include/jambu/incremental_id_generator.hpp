#include <mutex>
#include <string>
#include "../utils/file_helper.hpp"
#include "../utils/singleton.hpp"

namespace jambu {

// incremental id generator
template <typename T, typename Mutex>
class incremental_id_generator {
 public:
  using type = T;
  using mutex_type = Mutex;

  incremental_id_generator() : file_{}, start_value_{} {}

  void set_attributes(const std::string& filename, const T& init = T{}) {
    std::lock_guard<Mutex> l{mutex_};
    file_ = filename;
    start_value_ = init;
  }

  auto next_id() {
    std::lock_guard<Mutex> l{mutex_};
    auto value{start_value_};
    detail::file_helper fh{file_};
    auto status = fh.create_or_open();
    if (status == detail::file_open_status::error) {
      throw;
    }
    if (status == detail::file_open_status::opened) {
      // existing file - read the existing value, increment & write back
      T id{};
      fh.read_record_n(0, id);
      fh.write_record_n(0, ++id);
      value = id;
    } else {
      // new file - write the initial value
      fh.write_record_n(0, start_value_);
    }
    return value;
  }

 private:
  std::string file_;
  T start_value_;
  Mutex mutex_;
};

// global incremental id generator is just a singleton wrapper
// around incremental id generator.
template <typename T, typename Mutex = std::mutex>
struct g_incremental_id_generator
    : public detail::singleton<incremental_id_generator<T, typename Mutex>> {};
}  // namespace jambu
