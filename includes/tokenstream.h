#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include <string>
#include <iostream>
#include <vector>
#include <cstdint>

enum TokenType { 
  // KEYWORDS
  FUNC,
  LOOP,
  IF,
  ELSE,
  VAR,
  RETURN,

  // BINARY OPERATORS
  EQUAL,
  N_EQUAL,
  PLUS,
  SLASH,
  STAR,
  MINUS,
  R_ARROW,
  L_ARROW,

  // UNARY OPERATORS
  NOT,

  ID,
  TYPE,
  SET,

  // BLOCK SEPERATORS
  L_PAR,
  R_PAR,
  L_BRACKET,
  R_BRACKET,

  // CONSTANTS
  INT_CONST,
  FLOAT_CONST,
  STRING_CONST,

  SEMI,
  COMMA,

  SOI, // START OF INPUT
  EOI, // END OF INPUT

  EMPTY
};

class Token {
public:
  TokenType type;
  std::string id;
  uint16_t val;

  Token(TokenType t) : type(t) {};
  Token() {};

  friend std::ostream& operator<< (std::ostream& iostream, const Token& token) {
    switch (token.type)
    {
      case FUNC: iostream << "FUNC" << std::flush; break;
      case LOOP: iostream << "LOOP" << std::flush; break;
      case IF: iostream << "IF" << std::flush; break;
      case ELSE: iostream << "ELSE" << std::flush; break;
      case VAR: iostream << "VAR" << std::flush; break;
      case RETURN: iostream << "RETURN" << std::flush; break;
      case ID: iostream << "ID(" << token.id << ")" << std::flush; break;
      case TYPE: iostream << "TYPE(" << token.id << ")" << std::flush; break;
      case NOT: iostream << "NOT" << std::flush; break;
      case EQUAL: iostream << "EQUAL" << std::flush; break;
      case N_EQUAL: iostream << "N_EQUAL" << std::flush; break;
      case MINUS: iostream << "MINUS" << std::flush; break;
      case PLUS: iostream << "PLUS" << std::flush; break;
      case STAR: iostream << "STAR" << std::flush; break;
      case SLASH: iostream << "SLASH" << std::flush; break;
      case SET: iostream << "SET" << std::flush; break;
      case INT_CONST: iostream << "INT_CONST(" << token.val << ")" << std::flush; break;
      case SEMI: iostream << "SEMI" << std::flush; break;
      case EOI: iostream << "EOI" << std::flush; break;
      case SOI: iostream << "SOI" << std::flush; break;
      case L_PAR: iostream << "L_PAR" << std::flush; break;
      case R_PAR: iostream << "R_PAR" << std::flush; break;
      case L_BRACKET: iostream << "L_BRACKET" << std::flush; break;
      case R_BRACKET: iostream << "R_BRACKET" << std::flush; break;
      default: iostream << token.type << std::flush; break;
    }

    return iostream;
  }
};


class TokenStream {
private:
  std::string keywords[7] = { "fn", "loop", "if", "else", "var", "return", "NULL" };
  std::string types[7] = { "int", "float", "NULL" };

  int c = SOI;
  int current_line = 1;

  void next_char();
  bool mem_in_types(char mem_name[100]);

public:
  Token current_token;
  void next();
  int has_input();
  int get_current_line();
};

#endif /* TOKENSTREAM_H */
