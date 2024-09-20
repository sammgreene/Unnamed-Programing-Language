#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "expressions.h"

class Statement {
public:
  virtual ~Statement();
  virtual void print(int depth) = 0;
};

class Body {
  std::vector<Statement*> statements;
public:
  void add_statement(Statement* statement);
  void print(int depth);
};

class RegularStatement : public Statement {
  Expr* expression;
public:
  RegularStatement();
  RegularStatement(Expr* e);

  void print(int depth);
};
class ReturnStatement : public Statement {
  Expr* value;
public:
  ReturnStatement();
  ReturnStatement(Expr* v);

  void print(int depth);
};
class IfStatement : public Statement {
  Expr* condition;
  Body* if_body;
  Body* else_body;
public:
  IfStatement();
  IfStatement(Expr* c, Body* i, Body* e);

  void print(int depth);
};
class FuncStatement : public Statement {
  SymbolExpr* id;
  std::vector<Expr*> arguments;
  Body* body;
public:
  FuncStatement();
  FuncStatement(SymbolExpr* i, std::vector<Expr*> a, Body* b);

  void print(int depth);
};
class AssignStatement : public Statement {
  SymbolExpr* id;
  Expr* value;
public:
  AssignStatement();
  AssignStatement(SymbolExpr* i, Expr* v);

  void print(int depth);
};

#endif /* STATEMENTS_H */
