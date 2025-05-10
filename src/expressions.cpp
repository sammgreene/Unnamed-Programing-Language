#include "../includes/expressions.h"

#include <iostream>

LiteralExpr::LiteralExpr() {};
LiteralExpr::LiteralExpr(int v) : int_value(v) { type = Type::INT; }
LiteralExpr::LiteralExpr(float v) : float_value(v) { type = Type::FLOAT; }

SymbolExpr::SymbolExpr() {}
SymbolExpr::SymbolExpr(std::string i) : id(i) {}

BinaryExpr::BinaryExpr() {}
BinaryExpr::BinaryExpr(Operator o) : op(o) {}

CallExpr::CallExpr() {}
CallExpr::CallExpr(std::string i, std::vector<Expr*> a) : id(i), arguments(a) {}

Operator BinaryExpr::binding_power() {
  return op;
}

std::string op_string(Operator op) {
  switch (op) {
    case Operator::ZERO_BINDING_POWER: return "ZERO_BINDING_POWER";
    case Operator::ADD: return "ADD";
    case Operator::SUB: return "SUB";
    case Operator::MULT: return "MULT";
    case Operator::DIV: return "DIV";
    case Operator::EQUALS: return "EQUALS";
    case Operator::NOT_EQUALS: return "NOT_EQUALS";
    case Operator::ABSOLUTE_BINDING_POWER: return "ABSOLUTE_BINDING_POWER";
  }
  return "";
}

void SymbolExpr::print(std::string name, int depth) {
  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  std::cout << name << "SymbolExpr: { " << id << " }" << std::endl;
}
void LiteralExpr::print(std::string name, int depth) {
  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  if (type == Type::INT) {
    std::cout << name << "LiteralExpr: { " << int_value << " }" << std::endl;
  }
  if (type == Type::FLOAT) {
    std::cout << name << "LiteralExpr: { " << float_value << " }" << std::endl;
  }
}
void BinaryExpr::print(std::string name, int depth) {
  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  std::cout << name << "BinaryExpr: {" << std::endl;

  left->print("left: ", depth + 1);

  for (int i=0;i<depth+1;i++) {
    std::cout << "  ";
  }
  std::cout << "op: " << op_string(op) << std::endl;

  right->print("right: ", depth + 1);

  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  std::cout << "}" << std::endl;
}
void CallExpr::print(std::string name, int depth) {
  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  std::cout << name << "CallExpr: {" << std::endl;

  for (int i=0;i<depth+1;i++) {
    std::cout << "  ";
  }
  std::cout << "id: " << id << std::endl;

  for (int i=0;i<arguments.size();i++) {
    arguments[i]->print("arg" + std::to_string(i) + ": ", depth + 1);
  }

  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  std::cout << "}" << std::endl;
}
