#include "../includes/error.h"

#include <iostream>

template <typename T>
bool contains(std::vector<T> v, T x) {
  return std::find(v.begin(), v.end(), x) != v.end();
}

void ErrorHandler::error(std::string error_type, std::string error_msg) {
  std::cout << stream->get_file_name() << ":" << stream->get_line() << " ";
  std::cout << "\033[0;31m" << error_type << ": " << "\033[0m" << error_msg << std::endl;
  exit(1);
}
void ErrorHandler::expect_or_error(std::vector<TokenType> tokens, std::string error_type, std::string error_msg) {
  if (!contains(tokens, stream->current_token.type)) error(error_type, error_msg);
}

void ErrorHandler::se(std::string error_msg) {
  error("syntax error", error_msg);
}
void ErrorHandler::ese(std::vector<TokenType> tokens, std::string error_msg) {
  expect_or_error(tokens, "syntax error", error_msg);
}
