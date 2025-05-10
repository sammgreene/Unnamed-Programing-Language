#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <vector>

enum class Type {
  INT,
  FLOAT
};
enum class Operator {
  ZERO_BINDING_POWER = 0,
  EQUALS,
  NOT_EQUALS,
  ADD,
  SUB,
  MULT,
  DIV,
  ABSOLUTE_BINDING_POWER
};

class Expr {
public:
  virtual ~Expr() {};
  virtual void print(std::string name, int depth) = 0;
};

class SymbolExpr : public Expr {
  std::string id;
public:
  SymbolExpr();
  SymbolExpr(std::string id);

  void print(std::string name, int depth);
};

class LiteralExpr : public Expr {
  Type type;
  int int_value;
  float float_value;
public:
  LiteralExpr();
  LiteralExpr(int v);
  LiteralExpr(float v);

  void print(std::string name, int depth);
};

class BinaryExpr : public Expr {
  Operator op;
public:
  Expr* left;
  Expr* right;

  BinaryExpr();
  BinaryExpr(Operator op);

  Operator binding_power();

  void print(std::string name, int depth);
};
class CallExpr : public Expr {
  std::string id;
  std::vector<Expr*> arguments;
public:
  CallExpr();
  CallExpr(std::string i, std::vector<Expr*> a);

  void print(std::string name, int depth);
};

#endif /* EXPRESSIONS_H */
