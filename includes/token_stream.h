#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <string>
#include <fstream>
#include <vector>

enum TokenType {
  // KEYWORDS
  FUNC,
  IF,
  ELSE,
  RETURN,
  ID,

  TYPE,

  INT_CONST,
  FLOAT_CONST,
  // BINARY OPERATORS
  PLUS,
  MINUS,
  STAR,
  SLASH,
  EQUAL,
  NOT_EQUAL,
  R_ARROW,
  L_ARROW,

  // UNARY OPERATORS
  NOT,

  // CODE SECTIONS
  L_PAREN,
  R_PAREN,
  L_BRACKET,
  R_BRACKET,
  
  // ACTIONS
  SET,

  SEMI,
  COMMA,

  SOI,
  EOI
};

class Token {
public:
  TokenType type;
  std::string id;
  int int_value;
  float float_value;


  Token(TokenType t, int v);
  Token(TokenType t, float f);
  Token(TokenType t, std::string i);
  Token(TokenType t);

  std::string to_str();

  friend std::ostream& operator<<(std::ostream& ostream, Token& token) {
    switch (token.type) {
      // KEYWORDS
      case FUNC: ostream << "FUNC"; break;
      case IF: ostream << "IF"; break;
      case ELSE: ostream << "ELSE"; break;
      case RETURN: ostream << "RETURN"; break;
      case ID: ostream << "ID(" << token.id << ")"; break;

      case TYPE: ostream << "TYPE(" << token.id << ")"; break;

      case INT_CONST: ostream << "INT_CONST(" << token.int_value << ")"; break;
      case FLOAT_CONST: ostream << "FLOAT_CONST(" << token.float_value << ")"; break;

      // BINARY OPERATORS
      case PLUS: ostream << "PLUS"; break;
      case MINUS: ostream << "MINUS"; break;
      case STAR: ostream << "STAR"; break;
      case SLASH: ostream << "SLASH"; break;
      case EQUAL: ostream << "EQUAL"; break;
      case NOT_EQUAL: ostream << "NOT_EQUAL"; break;
      case R_ARROW: ostream << "R_ARROW"; break;
      case L_ARROW: ostream << "L_ARROW"; break;

      // UNARY OPERATORS
      case NOT: ostream << "NOT"; break;

      // CODE SECTIONS
      case L_PAREN: ostream << "L_PAREN"; break;
      case R_PAREN: ostream << "R_PAREN"; break;
      case L_BRACKET: ostream << "L_BRACKET"; break;
      case R_BRACKET: ostream << "R_BRACKET"; break;

      // ACTIONS
      case SET: ostream << "SET"; break;

      case SEMI: ostream << "SEMI"; break;
      case COMMA: ostream << "COMMA"; break;

      case SOI: ostream << "SOI"; break;
      case EOI: ostream << "EOI"; break;
      default: ostream << token.type; break;
    }
    return ostream;
  }
};

class TokenStream {
  std::ifstream in;
  std::string file_name;
  char c = EOI;

  int current_line;

  std::vector<std::string> keywords;
  std::vector<std::string> types;

  void next_char();
public:
  Token current_token;
  TokenStream(std::string file_path);

  void next();
  void print_token();

  int get_line();
  std::string get_file_name();
  bool has_input();
};

#endif /* TOKEN_STREAM_H */
