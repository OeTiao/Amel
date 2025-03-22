#ifndef LEXER
#define LEXER
#include "token.h"
#include <stddef.h>
#include <string.h>
size_t tokenize(char *src, token **tokens_ptr);

#endif
