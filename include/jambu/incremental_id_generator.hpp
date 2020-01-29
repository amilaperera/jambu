#include <mutex>
#include <string>
#include "../utils/record_file.hpp"
#include "../utils/singleton.hpp"

namespace jambu {

// incremental id generator
template <typename T, typename Mutex = std::mutex>
class incremental_id_generator {
 public:
  using type = T;
  using mutex_type = Mutex;

  incremental_id_generator() : start_value_{} {}

  void set_attributes(const std::string& filename, const T& init = T{}) {
    std::lock_guard<Mutex> l{mutex_};
    file_ = filename;
    start_value_ = init;
  }

  auto next_id() {
    std::lock_guard<Mutex> l{mutex_};
    auto value{start_value_};
    detail::record_file file{file_};
    auto status = file.create_or_open();
    if (status == detail::file_open_status::error) {
      throw;
    }
    if (status == detail::file_open_status::opened) {
      // existing file - read the existing value, increment & write back
      T id{};
      file.read_record(0, id);
      file.write_record(0, ++id);
      value = id;
    } else {
      // new file - write the initial value
      file.write_record(0, start_value_);
    }
    return value;
  }

 private:
  T start_value_;
  std::string file_;
  Mutex mutex_;
};

// global incremental id generator is just a singleton wrapper
// around incremental id generator.
template <typename T, typename Mutex = std::mutex>
struct g_incremental_id_generator
    : public detail::singleton<incremental_id_generator<T, typename Mutex>> {};
}  // namespace jambu
