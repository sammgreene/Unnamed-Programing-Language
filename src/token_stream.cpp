#include "../includes/token_stream.h"

#include <iostream>

bool is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
bool is_numeric(char c) {
  return (c >= '0' && c <= '9') || c == '.';
}
template <typename T>
bool contains(std::vector<T> v, T x) {
  return std::find(v.begin(), v.end(), x) != v.end();
}


Token::Token(TokenType t, int v) : type(t), int_value(v) {}
Token::Token(TokenType t, float f) : type(t), float_value(f) {}
Token::Token(TokenType t, std::string i) : type(t), id(i) {}
Token::Token(TokenType t) : type(t) {}

int TokenStream::get_line() {
  return current_line;
}
std::string TokenStream::get_file_name() {
  return file_name;
}

TokenStream::TokenStream(std::string file_path) : current_token(Token(SOI)) {
  in.open(file_path);
  file_name = file_path;
  current_line = 1;
  next_char();
  keywords = { "fn", "if", "else", "return", "NULL" };
  types = { "int", "float" };
}

bool TokenStream::has_input() {
  return current_token.type != EOI;
  if (in) return true;
  return false;
}

void TokenStream::next_char() {
  if (in) {
    in.get(c);
  }
  else {
    current_token.type = EOI;
  }
}

std::string Token::to_str() {
  switch (type) {
    // KEYWORDS
    case FUNC: return "FUNC"; break;
    case IF: return "IF"; break;
    case ELSE: return "ELSE"; break;
    case RETURN: return "RETURN"; break;
    case ID: return "ID(" + id + ")"; break;

    case TYPE: return "TYPE(" + id + ")"; break;

    case INT_CONST: return "INT_CONST(" + std::to_string(int_value) + ")"; break;
    case FLOAT_CONST: return "FLOAT_CONST(" + std::to_string(float_value) + ")"; break;

    // BINARY OPERATORS
    case PLUS: return "PLUS"; break;
    case MINUS: return "MINUS"; break;
    case STAR: return "STAR"; break;
    case SLASH: return "SLASH"; break;
    case EQUAL: return "EQUAL"; break;
    case NOT_EQUAL: return "NOT_EQUAL"; break;
    case R_ARROW: return "R_ARROW"; break;
    case L_ARROW: return "L_ARROW"; break;

    // UNARY OPERATORS
    case NOT: return "NOT"; break;

    // CODE SECTIONS
    case L_PAREN: return "L_PAREN"; break;
    case R_PAREN: return "R_PAREN"; break;
    case L_BRACKET: return "L_BRACKET"; break;
    case R_BRACKET: return "R_BRACKET"; break;

    // ACTIONS
    case SET: return "SET"; break;

    case SEMI: return "SEMI"; break;
    case COMMA: return "COMMA"; break;

    case SOI: return "SOI"; break;
    case EOI: return "EOI"; break;
    default: return std::to_string(type); break;
  }
}

void TokenStream::next() {
  bool loop = true;
  while (loop && has_input()) {
    loop = false;
    switch (c) {
      case '\n': current_line++;
      case ' ': loop = true; next_char(); break;

      case '+': current_token = Token(PLUS); next_char(); break;
      case '-': current_token = Token(MINUS); next_char(); break;
      case '*': current_token = Token(STAR); next_char(); break;
      case '/': current_token = Token(SLASH); next_char(); break;

      case '>': current_token = Token(R_ARROW); next_char(); break;
      case '<': current_token = Token(L_ARROW); next_char(); break;

      case '(': current_token = Token(L_PAREN); next_char(); break;
      case ')': current_token = Token(R_PAREN); next_char(); break;

      case '{': current_token = Token(L_BRACKET); next_char(); break;
      case '}': current_token = Token(R_BRACKET); next_char(); break;

      case ';': current_token = Token(SEMI); next_char(); break;
      case ',': current_token = Token(COMMA); next_char(); break;

      case ':': current_token = Token(SET); next_char(); break;

      case '!': {
                  next_char();
                  if (c == '=') current_token = Token(NOT_EQUAL);
                  else current_token = Token(NOT);
                  next_char();
                }; break;
      case '=': {
                  next_char();
                  if (c == '=') current_token = Token(EQUAL);
                  else {} // should error
                  next_char();
                }; break;

      case 'a'...'z':
      case 'A'...'Z':
      case '_': {
                  char mem_name[100];
                  
                  int i = 0;
                  while (is_alpha(c)) {
                    mem_name[i] = c;
                    i++;
                    next_char();
                  }
                  mem_name[i] = '\0';

                  int index = 0;
                  while (keywords[index] != "NULL" && mem_name != keywords[index]) {
                    index++;
                  }

                  current_token = Token(static_cast<TokenType>(index), mem_name);
                  if (contains(types, std::string(mem_name))) current_token = Token(TYPE, mem_name);

                }; break;

      case '0'...'9': {
                        bool is_float = false;
                        char mem_val[100];

                        int i = 0;
                        while (is_numeric(c)) {
                          if (c == '.') {
                            if (is_float) {} // error / cant be a float twice!!
                            else is_float = true;
                          }
                          mem_val[i] = c;
                          i++;
                          next_char();
                        }
                        mem_val[i] = '\0';

                        if (is_float) current_token = Token(FLOAT_CONST, std::stof(mem_val));
                        else current_token = Token(INT_CONST, std::stoi(mem_val));

                      }; break;
      default: next_char(); break;
    } // switch case
  }
  std::cout << current_token << std::endl;
}
