#include <iostream>
#include "../include/jambu/incremental_id_generator.hpp"

int main(int argc, char *argv[]) {
  std::cout << "First instantiation\n";
  jambu::incremental_id_generator<unsigned int> id_gen1("C:\\work\\test.data");
  std::cout << id_gen1.next_id() << std::endl;
  std::cout << id_gen1.next_id() << std::endl;
  std::cout << id_gen1.next_id() << std::endl;
  std::cout << id_gen1.next_id() << std::endl;
  std::cout << id_gen1.next_id() << std::endl;
  std::cout << id_gen1.next_id() << std::endl;
  std::cout << "Second instantiation\n";
  return 0;
}
