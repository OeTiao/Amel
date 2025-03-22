#include "lexer.h"
#include <malloc.h>
#include <stdio.h>

void advance_f(size_t *i, char *src, char *curr_char, size_t *line, size_t *column) {
    if (src[(*i)+1] != '\0') {
        (*i)++;
        *curr_char = src[*i];
        (*column)++;
        if(*curr_char == '\n')
            (*line)++; (*column) = 0;
        
    }
}

void tokens_pushback_f(token value, token **tokens, size_t *initialized_tokens, size_t *tokens_capacity) {
    if((*tokens_capacity) == (*initialized_tokens))
    {
        *tokens_capacity *= 2;
        *tokens = realloc((*tokens), *tokens_capacity);
        if(*tokens == NULL) {
            perror("Unable to expand the array of tokens.");
            return;
        }
    }
    (*tokens)[(*initialized_tokens)] = value;
    (*initialized_tokens)++;
}

size_t tokenize(char *src, token **tokens_ptr) {
    size_t tokens_capacity = 128;
    token *tokens = malloc(sizeof(token) * tokens_capacity);
    if(tokens == NULL) {
        perror("Unable to allocate the array of tokens.");
        return 0;
    }
    size_t initialized_tokens = 0;
    size_t src_len = strlen(src);
    size_t column = 1;
    size_t line = 1;
    size_t i = 0;
    token curr_token;
    char curr_char;
    #define advance() advance_f(&i, src, &curr_char, &line, &column);
    #define tokens_pushback() tokens_pushback_f(curr_token, &tokens, &initialized_tokens, &tokens_capacity)
    
    for(; i <= src_len; i++) {
        curr_char = src[i];
        switch(curr_char) {
            case '+':
                if(src[i+1] == '='){
                    advance();
                    curr_token.value = "+=";
                    curr_token.type = PLUS_EQ;
                    tokens_pushback();
                } else {
                    curr_token.value = "+";
                    curr_token.type = PLUS;
                    tokens_pushback();
                }
                break;
            case '-':

                break;
            case '*':

                break;
            case '/':

                break;
            case '%':

                break;
            case '>':

                break;
            case '<':

                break;
            case '!':

                break;
            case '=':

                break;
            case '(':

                break;

            case ')':

                break;
            case '{':

                break;
            case '}':

                break;
            case '[':

                break;
            case ']':

                break;
            case ';':

                break;
            case ':':

                break;
            case ',':

                break;
            case '.':

                break;
        }
        advance();
    }
    *tokens_ptr = tokens;
    return tokens_capacity;
}

