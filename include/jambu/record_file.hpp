#include <string>

namespace jambu {
namespace detail {
struct record_base {
 protected:
  record_base() : __jambu_record_id__{} {}
  unsigned long __jambu_record_id__;
};
}  // namespace detail
}  // namespace jambu

#define JAMBU_RECORD_START(NAME)                    \
  struct NAME : public jambu::detail::record_base { \
    friend class jambu::record_file<NAME>;

#define JAMBU_RECORD_END() \
  }                        \
  ;

namespace jambu {
template <typename T>
class record_file {
 public:
  explicit record_file(const std::string& file, unsigned long sz)
      : filename_{file}, size_{sz} {}
  void create(const T& rec) {}

 private:
  const std::string filename_;
  unsigned long size_;  // size in number of records
};
}  // namespace jambu