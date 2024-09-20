#include "../includes/parser.h"
#include "../includes/error.h"

#include <iostream>

#define OPERATORS { PLUS, MINUS, STAR, SLASH, EQUAL, NOT_EQUAL }

template <typename T>
bool contains(std::vector<T> v, T x) {
  return std::find(v.begin(), v.end(), x) != v.end();
}
bool Parser::token_matches(std::vector<TokenType> types) {
  return contains(types, stream.current_token.type);
}
bool Parser::token_matches(TokenType token_type) {
  return stream.current_token.type == token_type;
}
void Parser::expect(std::vector<TokenType> types, std::string error_msg) {
  error_handler.ese(types, error_msg);
}
void Parser::expect(TokenType type, std::string error_msg) {
  error_handler.ese({ type }, error_msg);
}

Expr* root_expression_from_token(Token token) {
  switch (token.type) {
    case TokenType::INT_CONST: return new LiteralExpr(token.int_value); break; // create this
    case TokenType::FLOAT_CONST: return new LiteralExpr(token.float_value); break;
    case TokenType::ID: return new SymbolExpr(token.id); break;
    default: return NULL; break;
  }
}
BinaryExpr* binary_expression_from_token(Token token) {
  switch (token.type) {
    case TokenType::PLUS: return new BinaryExpr(Operator::ADD); break; // create this
    case TokenType::MINUS: return new BinaryExpr(Operator::SUB); break;
    case TokenType::STAR: return new BinaryExpr(Operator::MULT); break;
    case TokenType::SLASH: return new BinaryExpr(Operator::DIV); break;
    case TokenType::EQUAL: return new BinaryExpr(Operator::EQUALS); std::cout << "\nEQAULS WUD\n" << std::endl; break;
    case TokenType::NOT_EQUAL: return new BinaryExpr(Operator::NOT_EQUALS); break;
    default: return NULL; break;
  }
}

CallExpr* Parser::create_call_expr(std::string mem_val) {
  // a(1, 2);
  //  ^
  expect(L_PAREN, "expected left paren to begin function call args");

  std::vector<Expr*> args = {};

  stream.next();
  // a(1, 2) + 1;
  //   ^
  while (!token_matches(R_PAREN)) {
    args.push_back(nud_expr());
    // a(1, 2);
    //    ^
    if (token_matches(R_PAREN)) break;
    expect(COMMA, "should find comma at end of first command\ngot: " + stream.current_token.to_str());
    stream.next();
  }

  CallExpr* call_expr = new CallExpr(mem_val, args);

  return call_expr;
}

Parser::Parser(std::string s) : stream(TokenStream(s)), error_handler(&stream) {}

void Parser::make_body(Body* body) {
  Statement* statement;

  while (stream.has_input()) {
    stream.next();
    switch (stream.current_token.type) {
      case TokenType::INT_CONST:
      case TokenType::ID:
      case TokenType::L_PAREN: statement = create_regular_statement(); break;

      case TokenType::FUNC: statement = create_function_statement(); break;

      case TokenType::IF: statement = create_if_statement(); break;

      case TokenType::RETURN: statement = create_return_statement(); break;

      case TokenType::TYPE: statement = create_assign_statement(); break;

      case TokenType::EOI:
      case TokenType::R_BRACKET: return; // found end of body
     
      default: error_handler.se("token: '" + stream.current_token.to_str() + "' does not match a pattern to start a new statement");
    }
    // a + 1;
    //      ^
    expect({SEMI, R_BRACKET}, "expected semi colon or right bracket at end of statement");
    body->add_statement(statement);
  }
}

void Parser::construct_tree() {
  Statement* statement;
  stream.next();

  while (stream.has_input()) {
    switch (stream.current_token.type) {
      case TokenType::INT_CONST:
      case TokenType::ID:
      case TokenType::L_PAREN: statement = create_regular_statement(); break;

      case TokenType::FUNC: statement = create_function_statement(); break;

      case TokenType::IF: statement = create_if_statement(); break;

      case TokenType::RETURN: statement = create_return_statement(); break;

      case TokenType::TYPE: statement = create_assign_statement(); break;

      case TokenType::EOI:
      case TokenType::R_BRACKET: return; // found end of body
     
      default: error_handler.se("token: '" + stream.current_token.to_str() + "' does not match a pattern to start a new statement");
    }
    // a + 1;
    //      ^
    if (token_matches(EOI) ) { ast.add_statement(statement); return; }
    expect({SEMI, R_BRACKET}, "expected semi colon or right bracket at end of statement");
    ast.add_statement(statement);
    stream.next();
  }
}

Expr* Parser::nud_expr() {
  Expr* left;
  std::string mem_val = "";
  if (stream.current_token.type == L_PAREN) {
    // 1 * (a + 2) * 3;
    //     ^
    int first_line = stream.get_line();
    stream.next();
    left = nud_expr();
    if (token_matches(COMMA)) { return left; }
    expect(R_PAREN, "expected paired right paren to left paren on line: " + std::to_string(first_line));
  }
  else {
    // (a + 2);
    //  ^
    expect({ID, INT_CONST, FLOAT_CONST}, "expected int, float, or id to start expression\n got: " + stream.current_token.to_str());
    if (token_matches(ID)) { mem_val = stream.current_token.id; }
    left = root_expression_from_token(stream.current_token);
  }

  stream.next();
  // (a) * 3;
  //   ^
  // (a) * 3;
  //        ^
  if ( token_matches({R_PAREN, SEMI}) ) return left;

  if ( token_matches(L_PAREN) && mem_val != "") {
    // (a() + 2) * 3;
    //   ^
    // TODO
    left = create_call_expr(mem_val);
    // (a() + 2) * 3;
    //    ^
    expect(R_PAREN, "expected closing paren to function call arguments");
    stream.next();
    // (a() + 2) * 3;
    //      ^
  }
  // (a + 2) * 3;
  //    ^
  if (!token_matches(OPERATORS)) {
    return left;
  }
  expect(OPERATORS, "expected operator, got: " + stream.current_token.to_str() + ", you may have intended to place a semi colon here");
  BinaryExpr* current_expression = binary_expression_from_token(stream.current_token);

  current_expression->left = left;

  stream.next();
  // (a + 2) * 3;
  //      ^

  Expr* return_expr = led_expr(current_expression);
  //expect(SEMI, "expected semi colon to end expression");

  std::cout << "FINISHED EXPRESSION" << std::endl;
  return return_expr;
}

BinaryExpr* Parser::led_expr(BinaryExpr* previous_expression) {
  Expr* left;
  std::string mem_val = "";
  if (stream.current_token.type == L_PAREN) {
    // 1 * (a + 2) * 3;
    //     ^
    int first_line = stream.get_line();
    stream.next();
    if (stream.current_token.type == R_PAREN) {
      return NULL; // empty parens
    }
    left = nud_expr();
  if ( token_matches(COMMA) ) {
    previous_expression->right = left;
    return previous_expression;
  }
    expect(R_PAREN, "expected paired right paren to left paren on line: " + std::to_string(first_line));
  }
  else {
    // (a + 2);
    //  ^
    expect({ID, INT_CONST, FLOAT_CONST}, "expected int, float, or id to start expression\n got: " + stream.current_token.to_str());
    left = root_expression_from_token(stream.current_token);
  }

  stream.next();

  // (a) * 3;
  //   ^
  // (a) * 3;
  //        ^
  if ( token_matches({R_PAREN, SEMI}) ) {
    previous_expression->right = left;
    return previous_expression;
  }

  if ( token_matches(L_PAREN) && mem_val != "" ) {
    // (a() + 2) * 3;
    //   ^
    // TODO
    left = create_call_expr(mem_val);
    // (a() + 2) * 3;
    //    ^
    expect(R_PAREN, "expected closing paren to function call arguments");
    stream.next();
    // (a() + 2) * 3;
    //      ^
  }
  // (a + 2) * 3;
  //    ^
  if (!token_matches(OPERATORS)) {
    previous_expression->right = left;
    return previous_expression;
  }
  expect(OPERATORS, "expected operator, got: " + stream.current_token.to_str());
  BinaryExpr* current_expression = binary_expression_from_token(stream.current_token);

  // (a * 2 + 3) + 1;
  //        ^
  // 0 + a * 2 + 3;
  //       ^
  if (current_expression->binding_power() > previous_expression->binding_power()) {
    current_expression->left = left;
    stream.next();
    current_expression = led_expr(current_expression);
    previous_expression->right = current_expression;
    return previous_expression;
  }
  else {
    previous_expression->right = left;
    current_expression->left = previous_expression;
    stream.next();
    return led_expr(current_expression);
  }
}

Statement* Parser::create_regular_statement() {
  Statement* s = new RegularStatement(nud_expr());
  if (token_matches(R_PAREN)) {
    std::cout << "FUNNY EMPTY PARENS QUIRK: THIS SHOULD BE FIXED" << std::endl;
    // TODO
    // stream.next();
  }
  expect(SEMI, "semicolon required to end an expression statement");
  return s;
}

Statement* Parser::create_if_statement() {
  // if (a == b)
  // ^
  expect(IF, "expected if symbol to signifiy start of an if statement");
  stream.next();
  expect(L_PAREN, "expected left paren to being if statement condition");
  Expr* condition = nud_expr();
  expect(L_BRACKET, "expected right paren to end if statement condition");
  condition->print("", 0);

  Body* if_body = new Body();
  make_body(if_body);

  stream.next();
  if (!token_matches(ELSE)) return new IfStatement(condition, if_body, new Body());
  Body* else_body = new Body();
  make_body(else_body);

  return new IfStatement(condition, if_body, else_body);
}

Statement* Parser::create_return_statement() {}
Statement* Parser::create_function_statement() {}
Statement* Parser::create_assign_statement() {}

void Parser::print() {
  ast.print(0);
}
