#include <exception>
#include <string>

namespace jambu {
class jambu_ex : public std::exception {
 public:
  explicit jambu_ex(std::string msg) : msg_{std::move(msg)} {}
  const char* what() const noexcept override { return msg_.c_str(); }

 private:
  std::string msg_;
};

}  // namespace jambu