#include "../includes/parser.h"
#include "../includes/error.h"

// returns LiteralExpr or SymbolExpr
Expr* Parser::expr_from_curr_token() {
    switch (stream.current_token.type) {
    case TokenType::INT_CONST: return new LiteralExpr(stream.current_token.val); break;
    case TokenType::ID: return new SymbolExpr(stream.current_token.id); break;
    default: expect_or_error({INT_CONST, ID}, "expected INT_CONST or ID token"); exit(0);
  }
};

SymbolExpr* Parser::get_symbol_expr_from_curr_token() {
    switch (stream.current_token.type) {
    case TokenType::ID: return new SymbolExpr(stream.current_token.id); break;
    default: expect_or_error({ID}, "ID token"); exit(0);
  }
};

// returns LiteralExpr or SymbolExpr
Type Parser::get_current_token_type() {
  expect_or_error({TYPE}, "expected a TYPE token");
  if (stream.current_token.id == "int") { return INT; }
  if (stream.current_token.id == "float") { return FLOAT; }
  error(stream, "unknown error", "TOKEN is of type TYPE(), but id does not match any known types");
  exit(0);
};

BinaryOperator Parser::convert_token_to_operator() {
  switch (stream.current_token.type) {
    case TokenType::N_EQUAL: return NOT_EQUAL_OP; break;
    case TokenType::EQUAL: return EQUAL_OP; break;
    case TokenType::PLUS: return ADD_OP; break;
    case TokenType::MINUS: return SUB_OP; break;
    case TokenType::STAR: return MULT_OP; break;
    case TokenType::SLASH: return DIV_OP; break;
    default: expect_or_error({N_EQUAL, EQUAL, PLUS, MINUS, STAR, SLASH}, "expected an operator token but got something else"); exit(0);
  }
};

void Parser::expect_or_error(std::vector<TokenType> types, std::string err_str) {
  for (TokenType type : types) {
    if (stream.current_token.type == type) { return; };
  }
  syntax_error(stream, err_str);
  exit(0);
}

Expr* Parser::create_expression(BinaryOperator previous_binding_power) {
  expect_or_error({INT_CONST, FLOAT_CONST, ID, L_PAR}, "expected an integer const, float const, id, or left paren to start expression");
  if (stream.current_token.type == L_PAR) {
    stream.next();
    return create_expression(ZERO_BINDING_POWER);
  }
  // this will be either a Literal or a Symbol Expression
  Expr* l = expr_from_curr_token();
  
  // Goto next token;
  stream.next();
  // if token is a semicolon then return
  if (stream.current_token.type == R_PAR) {
    stream.next();
    if (stream.current_token.type == L_BRACKET) { // this is a special case for if statements
      return l;
    }
  }
  if (stream.current_token.type == SEMI) { stream.next(); return l; }
  else {}
  expect_or_error({N_EQUAL, EQUAL, PLUS, MINUS, STAR, SLASH}, "expected an operator at next position");
  BinaryExpr* current_expr = new BinaryExpr(convert_token_to_operator());
  // this will always be a BinaryExpr with the correct operator filled in

  // first call always has most binding power
  current_expr->left = l;

  stream.next(); // TOKEN IS NOW ON 4
  current_expr = led_expression(current_expr->binding_power(), current_expr);

  std::cout << "#---------------------#" << std::endl;
  std::cout << "# STATEMENT CONCLUDED #" << std::endl;
  std::cout << "#---------------------#" << std::endl;
  return current_expr;
};

BinaryExpr* Parser::led_expression(BinaryOperator previous_binding_power, BinaryExpr* previous_expr) {
  expect_or_error({INT_CONST, FLOAT_CONST, ID, L_PAR}, "expected an integer const, float const, id, or left paren to start expression");
  if (stream.current_token.type == L_PAR) {
    stream.next();
    return led_expression(ZERO_BINDING_POWER, previous_expr);
  }
  Expr* l = expr_from_curr_token();
  
  // Goto next token;
  stream.next();
  // if token is a semicolon then return
  if (stream.current_token.type == R_PAR) {
    stream.next();
    if (stream.current_token.type == L_BRACKET) { // this is a special case for if statements
      previous_expr->right = l;
      return previous_expr;
    }
    previous_binding_power = ABSOLUTE_BINDING_POWER;
  }
  if (stream.current_token.type == SEMI) {
    previous_expr->right = l;
    stream.next();
    return previous_expr;
  }
  expect_or_error({N_EQUAL, EQUAL, PLUS, MINUS, STAR, SLASH}, "expected an operator at next position");
  BinaryExpr* current_expr = new BinaryExpr(convert_token_to_operator());
  // this will always be a BinaryExpr with the correct operator filled in

  if (current_expr->has_higher_binding_power(previous_binding_power)) {
    current_expr->left = l;
    stream.next();
    current_expr = led_expression(current_expr->binding_power(), current_expr);
    previous_expr->right = current_expr;
    return previous_expr;
  }
  else {
    previous_expr->right = l;
    current_expr->left = previous_expr;
    stream.next();
    current_expr = led_expression(current_expr->binding_power(), current_expr);
  }
  return current_expr;

};

Expression* Parser::create_regular_expr() {
  return new Expression(create_expression(ZERO_BINDING_POWER));
}

Assignment* Parser::create_assignment() {
  // current token should be a type
  // {int} a := 1 + 2;
  Type kind = get_current_token_type();
  stream.next();
  // int {a} := 1 + 2;
  SymbolExpr* symbol = get_symbol_expr_from_curr_token();

  stream.next();
  // int a {:=} 1 + 2;
  expect_or_error({SET}, "expected a set operator in variable decleration");

  stream.next();
  // int a := {1} + 2;
  Expr* expr = create_expression(ZERO_BINDING_POWER);

  return new Assignment(kind, symbol, expr);
};

If* Parser::create_if_statement() {
  // current token should be an if statement
  // if (a == 1;) {} else {}
  // ^
  expect_or_error({IF}, "expected 'if' to start an if statement"); // this will never throw and error but for readability
                                                                   //
  stream.next();
  // if (a == 1;) {} else {}
  //    ^

  expect_or_error({L_PAR}, "expected an expression wrapped in parenthesies");

  stream.next();
  // if (a == 1;) {} else {}
  //     ^
  expect_or_error({INT_CONST, FLOAT_CONST, ID}, "expected an int, float, or id to being if statement conditional");
  
  Expr* condition = create_expression(ZERO_BINDING_POWER);
  // if (a == 1;) {} else {}
  //              ^
  expect_or_error({L_BRACKET}, "expected and opening left bracket to begin if statement body");

  Body* if_body = create_bracketed_body();
  // if (a == 1;) {} else {}
  //               ^
  expect_or_error({R_BRACKET}, "expected closing right bracket after if statement body");
  
  stream.next();
  // if (a == 1;) {} else {}
  //                 ^
  if (stream.current_token.type != ELSE) {
    Body* else_body = new Body();
    // else_body->add_statement( new Expression(new LiteralExpr(0)) ); // empty body

    return new If(condition, if_body, else_body);
  }
  // stream.current_token.type == ELSE
  expect_or_error({ELSE}, "expected else statement after if statement");

  stream.next();
  // if (a == 1;) {} else {}
  //                      ^
  expect_or_error({L_BRACKET}, "expected and opening left bracket to begin if statement body");

  Body* else_body = create_bracketed_body();
  // if (a == 1;) {} else {}
  //                       ^
  expect_or_error({R_BRACKET}, "expected closing right bracket after else statement body");

  stream.next();

  return new If(condition, if_body, else_body);
};

Return* Parser::create_return_statement() {
  expect_or_error({RETURN}, "expected a return keyword");

  stream.next();
  Expr* return_expr = create_expression(ZERO_BINDING_POWER);

  return new Return(return_expr);
};

Statement* Parser::create_statement() {
  Statement* statement;
  switch (stream.current_token.type) {
    case TokenType::ID:
    case TokenType::L_PAR:
    case TokenType::INT_CONST: statement = create_regular_expr(); break;
    case TokenType::TYPE: statement = create_assignment(); break;
    case TokenType::IF: statement = create_if_statement(); break;
    case TokenType::RETURN: statement = create_return_statement(); break;
    default: break;
  }
  return statement;
};

Body* Parser::create_primary_body() {
  Body* body = new Body();
  while (stream.current_token.type != EOI) {
    body->add_statement(create_statement());
  }
  return body;
}
Body* Parser::create_bracketed_body() {
  expect_or_error({L_BRACKET}, "expected left bracket in default bracketed body decleration");
  stream.next();
  Body* body = new Body();
  while (stream.current_token.type != R_BRACKET) {
    body->add_statement(create_statement());
    if (!stream.has_input()) {
      syntax_error(stream, "reached end of input before a closing right bracket: '}'");
    }
  }
  expect_or_error({R_BRACKET}, "expected right bracket in end of default bracketed body decleration");
  return body;
}

void Parser::create_tree() {
  stream.next();
  ast.body = create_primary_body();
};

void Parser::print() {
  ast.print();
}
