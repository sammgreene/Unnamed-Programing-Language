#include "includes/parser.h"
#include <iostream>

int main() {
  Parser p = Parser("example.upl");

  p.construct_tree();
  p.print();

  return 0;
};
