#pragma once
#include "token.h"
#include <stddef.h>
#include <string.h>
token *tokenize(char *src, size_t *initialized_tokens_ptr);

