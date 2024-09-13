#include "../includes/error.h"
#include "../includes/tokenstream.h"

bool TokenStream::mem_in_types(char mem_name[100]) {
  int i = 0;
  while (types[i] != "NULL") {
    if (types[i] == mem_name) {
      return true;
    }
    i++;
  }
  return false;
}

void TokenStream::next_char() {
  c = getchar();
}

int TokenStream::has_input() {
  return (current_token.type != EOI);
}

void TokenStream::next() {
again:
  switch (c)
  {
    case '\n': current_line++;
    case ' ': case SOI: next_char(); goto again;
    case EOF: next_char(); current_token.type = EOI; break;
    case '-': next_char(); current_token.type = MINUS; break;
    case '+': next_char(); current_token.type = PLUS; break;
    case '*': next_char(); current_token.type = STAR; break;
    case '/': next_char(); current_token.type = SLASH; break;
    case ';': next_char(); current_token.type = SEMI; break;
    case '(': next_char(); current_token.type = L_PAR; break;
    case ')': next_char(); current_token.type = R_PAR; break;
    case '{': next_char(); current_token.type = L_BRACKET; break;
    case '}': next_char(); current_token.type = R_BRACKET; break;
    case '=': {
                next_char();
                if (c == '=') { next_char(); current_token.type = EQUAL; break; }
                else { syntax_error(*this, "single equal sign '=' is not defined in upl"); }
              }
    case ':': {
                next_char();
                if (c == '=') { next_char(); current_token.type = SET; break; }
                else { syntax_error(*this, "token ':' is not recognized, did you mean ':=', the set operator?"); }
              }
    case '!': {
                next_char();
                if (c == '=') { next_char(); current_token.type = N_EQUAL; break; }
                else { next_char(); current_token.type = NOT; break; }
              }
    default:  {  // handles numbers and letters // throws syntax errors
                if (c >= '0' && c <= '9')
                {
                  current_token.val = 0;
                  while (c >= '0' && c <= '9')
                  {
                    current_token.val *= 10;
                    current_token.val += c - '0';
                    next_char();
                  }
                  current_token.type = INT_CONST;
                }
                else if (c >= 'a' && c <= 'z')
                {
                  int i = 0;
                  char mem_name[100];
                  while (c >= 'a' && c <= 'z')
                  {
                    mem_name[i] = c;
                    i++;
                    next_char();
                  }
                  mem_name[i] = '\0';
                  // odd little trick to get the keywords
                  current_token.type = TokenType::FUNC;
                  while (keywords[current_token.type] != "NULL" && keywords[current_token.type] != mem_name) {
                    current_token.type = static_cast<TokenType>(static_cast<int>(current_token.type) + 1);
                  }
                  if (keywords[current_token.type] == "NULL") { current_token.type = ID; }
                  if (mem_in_types(mem_name)) { current_token.type = TYPE; }
                  current_token.id = mem_name;
                }
                else
                {
                  syntax_error(*this, "unknown char");
                }
              }
  }
  std::cout << current_token << std::endl;
}

int TokenStream::get_current_line() {
  return current_line;
}
