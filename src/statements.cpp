#include "../includes/statements.h"

#include <iostream>

void Body::add_statement(Statement* statement) {
  statements.push_back(statement);
}
void Body::print(int depth) {
  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  std::cout << "Body: {" << std::endl;

  for (Statement* statement : statements) {
    statement->print(depth + 1);
  }

  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  std::cout << "}" << std::endl;
}

Statement::~Statement() {}

RegularStatement::RegularStatement() {}
RegularStatement::RegularStatement(Expr* e) : expression(e) {}

ReturnStatement::ReturnStatement() {}
ReturnStatement::ReturnStatement(Expr* v) : value(v) {}

IfStatement::IfStatement() {}
IfStatement::IfStatement(Expr* c, Body* i, Body* e) : condition(c), if_body(i), else_body(e) {}

FuncStatement::FuncStatement() {}
FuncStatement::FuncStatement(SymbolExpr* i, std::vector<Expr*> a, Body* b) : id(i), arguments(a), body(b) {}

AssignStatement::AssignStatement() {}
AssignStatement::AssignStatement(SymbolExpr* i, Expr* v) : id(i), value(v) {}

void RegularStatement::print(int depth) {
  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  std::cout << "RegularStatement: {" << std::endl;

  expression->print("expr: ", depth + 1);

  for (int i=0;i<depth;i++) {
    std::cout << "  ";
  }
  std::cout << "}" << std::endl;
}
void ReturnStatement::print(int depth) {}
void IfStatement::print(int depth) {}
void FuncStatement::print(int depth) {}
void AssignStatement::print(int depth) {}
