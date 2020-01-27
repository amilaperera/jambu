#include <filesystem>
#include "../jambu/exception.hpp"
#include <fstream>
#include <string>

namespace jambu {
namespace detail {
enum class file_open_status { created, opened, error };

using record_index_type = size_t;

class file_helper {
 public:
  explicit file_helper(const std::string& file) : file_{file}, stream_{} {
    if (file_.empty()) {
      throw jambu_ex("empty filename");
    }
  }

  file_open_status create_or_open() {
    file_open_status status{file_open_status::opened};
    if (std::filesystem::exists(file_)) {
      stream_.open(file_, std::ios::in | std::ios::out | std::ios::binary);
    } else {
      stream_.open(file_, std::ios::out | std::ios::binary);
      status = file_open_status::created;
    }

    if (!stream_.is_open()) {
      status = file_open_status::error;
    }
    return status;
  }

  template <typename T>
  void read_record_n(record_index_type n, T& value) {
    // TODO: overflow detection ?
    std::ios::off_type offset = n * sizeof(T);
    stream_.seekg(offset, std::ios::beg);
    this->read(value);
  }

  template <typename T>
  void write_record_n(record_index_type n, const T& value) {
    // TODO: overflow detection ?
    std::ios::off_type offset = n * sizeof(T);
    stream_.seekp(offset, std::ios::beg);
    this->write(value);
  }

 private:
  template <typename T>
  void read(T& value) {
    stream_.read(reinterpret_cast<char*>(&value), sizeof(T));
  }

  template <typename T>
  void write(const T& value) {
    stream_.write(reinterpret_cast<const char*>(&value), sizeof(T));
  }

  const std::string file_;
  std::fstream stream_;
};

}  // namespace detail
}  // namespace jambu