#ifndef ERROR_H
#define ERROR_H

#include <string>
#include "../includes/tokenstream.h"
void error(TokenStream stream, std::string error_type, std::string error_message);
void syntax_error(TokenStream stream, std::string error_message);

#endif /* ERROR_H */
