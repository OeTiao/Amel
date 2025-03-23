#ifndef LEXER
#define LEXER
#include "token.h"
#include <stddef.h>
#include <string.h>
token *tokenize(char *src, size_t *initialized_tokens_ptr);

#endif
