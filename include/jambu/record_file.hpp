#include <string>
#include <mutex>

#include "../utils/os.hpp"
#include "incremental_id_generator.hpp"

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
template <typename RecordType>
class record_file {
 public:
  using IdType = unsigned long;
  using IdGenerator =
      jambu::incremental_id_generator<IdType>;

  record_file(const std::string& file, unsigned long sz,
              IdGenerator* id_generator)
      : filename_{file}, size_{sz}, id_generator_{id_generator} {}

  IdType create(const RecordType& rec) { 
    std::lock_guard<std::mutex> l{mutex_};
    auto rec_copy = rec;
    rec_copy.__jambu_record_id__ = id_generator_->next_id();
    return rec_copy.__jambu_record_id__;
  }

 private:
  const std::string filename_;
  unsigned long size_;  // size in number of records
  IdGenerator* id_generator_;
  std::mutex mutex_;
};
}  // namespace jambu