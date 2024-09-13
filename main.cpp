#include "includes/parser.h"
#include "includes/tokenstream.h"

int main() {
  Parser p;

  p.create_tree();
  p.print();

  return 0;
}
