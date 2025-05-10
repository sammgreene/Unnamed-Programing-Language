#ifndef ERROR_H
#define ERROR_H
#include "token_stream.h"

class ErrorHandler {
  TokenStream* stream;

public:
  ErrorHandler(TokenStream* s) : stream(s) {}

  void error(std::string error_type, std::string error_msg);
  void se(std::string error_msg);
  void expect_or_error(std::vector<TokenType>, std::string error_type, std::string error_msg);
  void ese(std::vector<TokenType>, std::string error_msg);
};

#endif /* ERROR_H */
