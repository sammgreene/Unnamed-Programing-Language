#ifndef PARSER_H
#define PARSER_H

#include "expressions.h"
#include "statements.h"
#include "token_stream.h"
#include "error.h"

typedef Operator BindingPower;

class Parser {
  Body ast;
  TokenStream stream;
  ErrorHandler error_handler;

  bool token_matches(std::vector<TokenType> types);
  bool token_matches(TokenType token_type);

  void expect(std::vector<TokenType> types, std::string error_msg);
  void expect(TokenType type, std::string error_msg);

  CallExpr* create_call_expr(std::string mem_val);

  Expr* nud_expr();
  BinaryExpr* led_expr(BinaryExpr* previous_expression);

  Statement* create_regular_statement();
  Statement* create_if_statement();
  Statement* create_return_statement();
  Statement* create_function_statement();
  Statement* create_assign_statement();

  void push_statement(Statement* statement);
  void make_body(Body* body);
public:
  Parser(std::string s);

  void construct_tree();

  void print();
};

#endif /* PARSER_H */
