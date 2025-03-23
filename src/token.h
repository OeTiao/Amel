#ifndef TOKEN
#define TOKEN

typedef enum {
    IDENTIFIER,
    KEYWORD,
    PLUS,
    MINUS,
    MUL,
    DIV,
    EQ,
    PLUS_EQ,
    MINUS_EQ,
    DIV_EQ,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_EQ,
    LESS_THAN_EQ,
    COMP_EQ,
    NOT,
    NOT_EQ,
    AND,
    MOD,
    MOD_EQ,
    OR,
    STRING,
    NIL,
    NUMBER,
    COMMA,
    SEMICOLON,
    COLON,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,
    AMEL_EOF,
} TOT;
typedef struct {
    TOT type;
    char *value;
    size_t index, line, column;
} token;
const char *keywords[] = 
{
    "if",
    "else",
    "elseif",
    "local",
    "while",
    "true",
    "false",
    "fn",
};
#endif