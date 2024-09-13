#include "../includes/parser_nodes.h"

void BinaryOperatorPrint(BinaryOperator op, int depth) {
  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  switch (op) {
    case ZERO_BINDING_POWER: std::cout << "ZERO_BINDING_POWER" << std::endl; break;
    case NOT_EQUAL_OP: std::cout << "NOT_EQUAL" << std::endl;  break;
    case EQUAL_OP: std::cout << "EQUAL" << std::endl;  break;
    case GREATER_OP: std::cout << "GREATER" << std::endl;  break;
    case LESS_OP: std::cout << "LESS" << std::endl;  break;
    case ADD_OP: std::cout << "ADD" << std::endl;  break;
    case SUB_OP: std::cout << "SUB" << std::endl;  break;
    case MULT_OP: std::cout << "MUL" << std::endl;  break;
    case DIV_OP: std::cout << "DIV" << std::endl;  break;
    case ABSOLUTE_BINDING_POWER: std::cout << "ABSOLUTE_BINDING_POWER" << std::endl;  break;
  }
}

void TypePrint(Type type, int depth) {
  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  switch (type) {
    case INT: std::cout << "INT" << std::endl;  break;
    case FLOAT: std::cout << "FLOAT" << std::endl;  break;
  }
}
