#include <iostream>
#include "../include/jambu/null_mutex.hpp"
#include "../include/jambu/incremental_id_generator.hpp"

int main(int argc, char *argv[]) {
  try {
    std::cout << "First instantiation\n";
    jambu::g_incremental_id_generator<unsigned int, jambu::detail::null_mutex> id_gen1;
    id_gen1.instance().set_attributes("C:\\work\\test.data", 100);
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << "Second instantiation\n";
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
    std::cout << id_gen1.instance().next_id() << std::endl;
  } catch (std::exception &ex) {
    std::cout << "Error: " << ex.what() << std::endl;
  }
  return 0;
}
