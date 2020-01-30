#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
                           // this in one cpp file
// catch configurations
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <iostream>
#include "../include/jambu/incremental_id_generator.hpp"
#include "../include/jambu/null_mutex.hpp"
#include "catch.hpp"

namespace test {
class file {
 public:
  explicit file(const std::string& f) : file_{f} {}
  explicit file(const char* f) : file_{f} {}
  ~file() { std::remove(file_.c_str()); }

 private:
  const std::string file_;
};
}  // namespace test

static constexpr const char* test_filename_1{"C:\\work\\test1.data"};

TEST_CASE("incremental id generator when file name empty",
          "[incremental_id_generator][construction]") {
  jambu::incremental_id_generator<unsigned int> id_generator;
  REQUIRE_THROWS_WITH(id_generator.next_id(),
                      Catch::Matchers::Contains("empty filename"));
}

TEST_CASE("incremental id generator when file name is non empty",
          "[incremental_id_generator][construction]") {
  test::file _{test_filename_1};

  jambu::incremental_id_generator<unsigned int> id_generator;
  id_generator.set_attributes(test_filename_1);
  REQUIRE_NOTHROW(id_generator.next_id());
}

TEST_CASE("incremental id generator incrementing values",
          "[incremental_id_generator]") {
  test::file _{test_filename_1};

  jambu::incremental_id_generator<unsigned int> id_generator;
  id_generator.set_attributes(test_filename_1);
  for (int i = 0; i < 10'000; ++i) {
    REQUIRE(id_generator.next_id() == i);
  }
}

TEST_CASE(
    "incremental id generator incrementing values starting from non default "
    "value",
    "[incremental_id_generator]") {
  test::file _{test_filename_1};

  jambu::incremental_id_generator<unsigned int> id_generator;
  id_generator.set_attributes(test_filename_1, 1'000U);
  for (int i = 0; i < 10'000; ++i) {
    REQUIRE(id_generator.next_id() == i + 1'000);
  }
}

TEST_CASE("global incremental id generation",
          "[global_incremental_id_generator]") {
  test::file _{test_filename_1};

  using id_generator = jambu::g_incremental_id_generator<unsigned int>;
  id_generator::instance().set_attributes(test_filename_1);
  for (int i = 0; i < 100; ++i) {
    REQUIRE(id_generator::instance().next_id() == i);
  }
  for (int i = 0; i < 100; ++i) {
    REQUIRE(id_generator::instance().next_id() == i + 100);
  }
}

#if 0
namespace test {
template<typename T, typename Mutex>
void run_id_generator(jambu::incremental_id_generator<T, Mutex>& id_generator,
                      int n) {
  for (int i = 0; i < n; ++i) {
    id_generator.next_id();
  }
}
}

TEST_CASE(
    "incremental id generator benchmarking with mutex", "[incremental_id_generator]") {
  test::file _{test_filename_1};

  jambu::incremental_id_generator<unsigned int> id_generator;
  id_generator.set_attributes(test_filename_1, 1'000U);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(id_generator.next_id() == i + 1'000);
  }
  BENCHMARK("next id incrments - 1") { return test::run_id_generator(id_generator, 1); };
}

TEST_CASE(
    "incremental id generator benchmarking with null mutex", "[incremental_id_generator]") {
  test::file _{test_filename_1};

  jambu::incremental_id_generator<unsigned int, jambu::null_mutex> id_generator;
  id_generator.set_attributes(test_filename_1, 1'000U);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(id_generator.next_id() == i + 1'000);
  }
  BENCHMARK("next id incrments - 1") { return test::run_id_generator(id_generator, 1); };
}
#endif
