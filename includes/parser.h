#ifndef PARSER_H
#define PARSER_H

#include "../includes/tokenstream.h"
#include "../includes/parser_nodes.h"

/*
enum { 
  PROG,
  INT_CONST,
  ID,
  PAREN_EXPR,

  FUNC_DEF,
  VAR_DEF,
  ASSIGN,
  IF_DEF,
  BLOCK,
  RETURN,

  // UNARY OPERATIONS
  NOT_OP,

  // BINARY OPERATIONS
  ADD_OP,
  SUB_OP,
  MUL_OP,
  DIV_OP,
  N_EQUAL_OP,
  EQUAL_OP
}; 
*/

class AST {
public:
  Body* body;
  void print() {
    body->print(0);
  }
};

class Parser {
public:
  void create_tree();
  void print();
private:
  TokenStream stream;

  Statement* create_statement();

  Expr* create_expression(BinaryOperator presidence);
  Expr* expr_from_curr_token();
  Expr* create_function_call(std::string id);
  std::vector<Expr*> get_function_call_arguments(std::vector<Expr*> args);

  SymbolExpr* get_symbol_expr_from_curr_token();
  std::vector<Parameter*> get_parameters(std::vector<Parameter*> previous);
  BinaryExpr* led_expression(BinaryOperator previous_binding_power, BinaryExpr* l);

  void expect_or_error(std::vector<TokenType> types, std::string err_str);

  BinaryOperator convert_token_to_operator();

  Type get_current_token_type();

  Body* create_primary_body();
  Body* create_bracketed_body();

  Expression* create_regular_expr();
  Assignment* create_assignment();
  If* create_if_statement();
  Return* create_return_statement();
  Function* create_function_statement();
  // Function* create_function_statement();

  AST ast;
};

#endif /* PARSER_H */
