#ifndef PARSER_NODES_H
#define PARSER_NODES_H

#include <iostream>
#include <vector>

enum BinaryOperator {
  ZERO_BINDING_POWER = 0,
  NOT_EQUAL_OP = 10,
  EQUAL_OP = 11,
  GREATER_OP = 20,
  LESS_OP = 21,
  ADD_OP = 30,
  SUB_OP = 31,
  MULT_OP = 40,
  DIV_OP = 41,
  ABSOLUTE_BINDING_POWER = 50
}; 
enum Type {
  INT = 1,
  FLOAT = 2
}; 

void BinaryOperatorPrint(BinaryOperator op, int depth);
void TypePrint(Type type, int depth);

class Expr {
public:
  virtual void print(int depth) = 0;
  virtual ~Expr() {};
};
class StringExpr : public Expr {
public:
  std::string str;
  StringExpr(std::string s) : str(s) {}
  StringExpr() {}
  void print(int depth) {
    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "StringExpr: " << str << std::endl;
  }
};
class LiteralExpr : public Expr {
public:
  int val;
  LiteralExpr(int v) : val(v) {}
  LiteralExpr() {}
  void print(int depth) {
    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "LiteralExpr: " << val << std::endl;
  }
};
class SymbolExpr : public Expr {
public:
  std::string id;
  SymbolExpr(std::string s) : id(s) {}
  SymbolExpr() {}
  void print(int depth) {
    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "SymbolExpr: " << id << std::endl;
  }
};
class BinaryExpr : public Expr {
public:
  Expr* left;
  BinaryOperator op;
  Expr* right;
  BinaryExpr(Expr* l, BinaryOperator o, Expr* r) : left(l), op(o), right(r) {}
  BinaryExpr(BinaryOperator o) : op(o) {}

  void print(int depth) {
    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "BinaryExpr: {" << std::endl;
    
    left->print(depth + 1);
    BinaryOperatorPrint(op, depth + 1);
    right->print(depth + 1);

    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "}" << std::endl;
  }

  bool has_higher_binding_power(BinaryExpr* other) {
    return (op / 10 > other->op / 10);
  }
  bool has_higher_binding_power(BinaryOperator oper) {
    return (op / 10 > oper / 10);
  }
  BinaryOperator binding_power() {
    return op;
  }

};

class Statement {
public:
  virtual void print(int depth) = 0;
  virtual ~Statement() {};
};

class Body {
  std::vector<Statement*> statements;
public:
  void print(int depth) {
    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "Body: {" << std::endl;

    for (Statement* statement : statements) {
      statement->print(depth+1);
    }

    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "}" << std::endl;
  };
  void add_statement(Statement* statement) {
    statements.push_back(statement);
  }
};

class Assignment : public Statement {
  Type kind;
  SymbolExpr* symbol;
  Expr* value;
public:
  Assignment() {};
  Assignment(Type k, SymbolExpr* s, Expr* e) : kind(k), symbol(s), value(e) {};

  void print(int depth) {
    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "Assignment: {" << std::endl;

    TypePrint(kind, depth + 1);

    symbol->print(depth + 1);
    value->print(depth + 1);

    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "}" << std::endl;
  };
};

class If: public Statement {
  Expr* condition;
  Body* if_body;
  Body* else_body;
public:
  If(Expr* c, Body* i, Body* e) : condition(c), if_body(i), else_body(e) {};

  void print(int depth) {
    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "IfStatement: {" << std::endl;
    condition->print(depth + 1);
    if_body->print(depth + 1);
    else_body->print(depth + 1);

    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "}" << std::endl;
  }
};

class Return : public Statement {
  Expr* return_value;
public:
  Return(Expr* r) : return_value(r) {};
  void print(int depth) {
    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "Return: {" << std::endl;

    return_value->print(depth + 1);

    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "}" << std::endl;
  }
};

class Expression : public Statement {
  Expr* expression;
public:
  Expression(Expr* e) : expression(e) {};
  Expression() {};

  void print(int depth) {
    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "Expression: {" << std::endl;

    expression->print(depth + 1);

    for (int i=0;i<depth;i++) {
      std::cout << "  ";
    }
    std::cout << "}" << std::endl;
  };
};

#endif /* PARSER_NODES_H */
