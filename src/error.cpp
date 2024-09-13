#include <iostream>
#include "../includes/tokenstream.h"

void error(TokenStream stream, std::string error_type, std::string error_message) {
  std::cout << "ERROR: " << error_type << " : " << stream.get_current_line() << std::endl;
  std::cout << "MSG: " << error_message << std::endl;
  std::cout << "CURRENT_TOKEN: " << stream.current_token << std::endl;
  std::cout << "CURRENT_MEM_VALUE: " << stream.current_token.id << std::endl;
  std::cout << "CURRENT_INT_VALUE: " << stream.current_token.val << std::endl;
  exit(0);
}

void syntax_error(TokenStream stream, std::string error_message) {
  error(stream, "syntax error", error_message);
}
