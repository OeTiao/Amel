#include <malloc.h> 
#include "lexer.h"
#include <stdio.h>
#include <string.h>  
#include <ctype.h>

size_t advance_f(size_t *i, char *src, char *curr_char, size_t *line, size_t *column) {
    if (src[*i + 1] != '\0') {
        (*i)++;  
        *curr_char = src[*i];  
        (*column)++; 

        
        if (*curr_char == '\n') {
            (*line)++;
            *column = 0;
        }

        return 0; 
    }

    return 1;
}


void tokens_pushback_f(token value, token **tokens, size_t *initialized_tokens, size_t *tokens_capacity, size_t line, size_t column, size_t index) {
    if ((*tokens_capacity) == (*initialized_tokens)) {
        *tokens_capacity *= 2;
        *tokens = realloc(*tokens, sizeof(token) * (*tokens_capacity));  
        if (*tokens == NULL) {
            perror("Unable to expand the array of tokens.");
            return;
        }
    }
    value.index = index;
    value.column = column;
    value.line = line;
    (*tokens)[(*initialized_tokens)] = value;  
    (*initialized_tokens)++; 
}

token *tokenize(char *src, size_t *initialized_tokens_ptr) {
    size_t tokens_capacity = 10;
    token *tokens = malloc(sizeof(token) * tokens_capacity);
    if (tokens == NULL) {
        perror("Unable to allocate the array of tokens.");
        return NULL;
    }
    size_t initialized_tokens = 0;
    size_t src_len = strlen(src);  
    size_t column = 1;
    size_t line = 1;
    size_t i = 0;
    token curr_token;
    char curr_char;
    #define advance() advance_f(&i, src, &curr_char, &line, &column)
    #define tokens_pushback() tokens_pushback_f(curr_token, &tokens, &initialized_tokens, &tokens_capacity, line, column, i)
    while (src[i] != '\0' && src[i+1] != '\0') {
        
        curr_char = src[i];
        
        switch(curr_char) {
            case '+':
                if (src[i + 1] == '=') {
                    advance();
                    curr_token.value = "+=";
                    curr_token.type = PLUS_EQ;
                } else {
                    curr_token.value = "+";
                    curr_token.type = PLUS;
                }
                tokens_pushback();
                break;
        
            case '-':
                if (src[i + 1] == '=') {
                    advance();
                    curr_token.value = "-=";
                    curr_token.type = MINUS_EQ;
                } else {
                    curr_token.value = "-";
                    curr_token.type = MINUS;
                }
                tokens_pushback();
                break;
        
            case '*':
                curr_token.value = "*";
                curr_token.type = MUL;
                tokens_pushback();
                break;
        
            case '/':
                if (src[i + 1] == '=') {
                    advance();
                    curr_token.value = "/=";
                    curr_token.type = DIV_EQ;
                } else {
                    curr_token.value = "/";
                    curr_token.type = DIV;
                }
                tokens_pushback();
                break;
        
            case '%':
                if (src[i + 1] == '=') {
                    advance();
                    curr_token.value = "%=";
                    curr_token.type = MOD_EQ;
                } else {
                    curr_token.value = "%";
                    curr_token.type = MOD;
                }
                tokens_pushback();
                break;
        
            case '>':
                if (src[i + 1] == '=') {
                    advance();
                    curr_token.value = ">=";
                    curr_token.type = GREATER_THAN_EQ;
                } else {
                    curr_token.value = ">";
                    curr_token.type = GREATER_THAN;
                }
                tokens_pushback();
                break;
        
            case '<':
                if (src[i + 1] == '=') {
                    advance();
                    curr_token.value = "<=";
                    curr_token.type = LESS_THAN_EQ;
                } else {
                    curr_token.value = "<";
                    curr_token.type = LESS_THAN;
                }
                tokens_pushback();
                break;
        
            case '=':
                if (src[i + 1] == '=') {
                    advance();
                    curr_token.value = "==";
                    curr_token.type = COMP_EQ;
                } else {
                    curr_token.value = "=";
                    curr_token.type = EQ;
                }
                tokens_pushback();
                break;
        
            case '!':
                if (src[i + 1] == '=') {
                    advance();
                    curr_token.value = "!=";
                    curr_token.type = NOT_EQ;
                } else {
                    curr_token.value = "!";
                    curr_token.type = NOT;
                }
                tokens_pushback();
                break;
        
            case ',':
                curr_token.value = ",";
                curr_token.type = COMMA;
                tokens_pushback();
                break;
        
            case ';':
                curr_token.value = ";";
                curr_token.type = SEMICOLON;
                tokens_pushback();
                break;
        
            case ':':
                curr_token.value = ":";
                curr_token.type = COLON;
                tokens_pushback();
                break;
        
            case '(':
                curr_token.value = "(";
                curr_token.type = LPAREN;
                tokens_pushback();
                break;
        
            case ')':
                curr_token.value = ")";
                curr_token.type = RPAREN;
                tokens_pushback();
                break;
        
            case '{':
                curr_token.value = "{";
                curr_token.type = LBRACE;
                tokens_pushback();
                break;
        
            case '}':
                curr_token.value = "}";
                curr_token.type = RBRACE;
                tokens_pushback();
                break;
        
            case '[':
                curr_token.value = "[";
                curr_token.type = LBRACKET;
                tokens_pushback();
                break;
        
            case ']':
                curr_token.value = "]";
                curr_token.type = RBRACKET;
                tokens_pushback();
                break;
        
            case '\0':
                curr_token.value = "EOF";
                curr_token.type = AMEL_EOF;
                tokens_pushback();
                break;
        
            default:
                
                if (isalpha(curr_char)) {
                    
                    char token_val[71] = {0}; 
                    size_t last_idx = 0;
                    
                    
                    token_val[last_idx] = curr_char;
                    last_idx++;
        
                
                    
                    if (isalnum(src[i+1])) {
                        if (last_idx == 70) {
                            printf("Error at index %zu, column %zu and line %zu: identifier is too long. Maximum size is 70 characters.", 
                                i+1, column, line);
                            return NULL;
                        }
                        advance();
                        token_val[last_idx] = curr_char;
                        last_idx++;
                        
                        while (isalnum(src[i+1])) {

                            if (last_idx == 70) {
                                printf("Error at index %zu, column %zu and line %zu: identifier is too long. Maximum size is 70 characters.", 
                                        i+1, column, line);
                                return NULL;
                            }
                            advance();
                            token_val[last_idx] = curr_char;
                            last_idx++;
                        }
                

                        token_val[last_idx] = '\0';
                        curr_token.value = _strdup(token_val);
                        curr_token.type = IDENTIFIER;
                    }
                    tokens_pushback();
                } 
                else if (curr_char >= '0' && curr_char <= '9') {
                   
                    size_t dot_count = 0;
                    char token_val[21] = {0}; 
                    size_t last_idx = 0;
                    
                    
                    token_val[last_idx] = curr_char;
                    last_idx = 1;
                
                    if (src[i+1] >= '0' && src[i+1] <= '9' || src[i+1] == '.') {
                        advance();
                        token_val[last_idx] = curr_char;
                        last_idx = 2;
                
                        while (src[i+1] >= '0' && src[i+1] <= '9' || src[i+1] == '.' && src[i+1] != '\0') {
                            
                            if (src[i+1] == '.' && dot_count > 0) {
                                printf("Error at index %zu, column %zu and line %zu: number is too long. Maximum size is 20 characters.", 
                                    i+1, column, line);
                                return NULL;
                            }
                            if (src[i+1] == '.') {
                                dot_count++;
                            }
                            if (last_idx >= 20) {  
                                printf("Error at index %zu, column %zu and line %zu: number is too long. Maximum size is 20 characters.", 
                                    i+1, column, line);
                                return NULL;
                            }
                
                            advance();
                            token_val[last_idx] = curr_char;
                            last_idx++;
                        }
                
                        
                       
                        token_val[last_idx] = '\0';
                        curr_token.value = _strdup(token_val);
                        curr_token.type = NUMBER;
                    }
                    tokens_pushback();
                } else if(curr_char == '"') {
                    
                }
                
                break;
        }
        advance();
        
    }
    *initialized_tokens_ptr = initialized_tokens;

    return tokens;

}
