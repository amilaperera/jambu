#include <iostream>
#include "../include/jambu/incremental_id_generator.hpp"

int main(int argc, char *argv[]) {
  try {
    std::cout << "First instantiation\n";
    jambu::g_incremental_id_generator<unsigned int> id_gen1;
    id_gen1.instance().set_attributes("", 100);
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
  } catch (const std::exception &ex) {
    std::cout << "Error: " << ex.what() << std::endl;
  }
  return 0;
}
