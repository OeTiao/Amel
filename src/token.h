#ifndef TOKEN
#define TOKEN

typedef enum {
    IDENTIFIER,
    IF,
    LOCAL,
    WHILE,
    END,
    FN,
    ELSE,
    ELSEIF,
    RETURN,
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
} token;
#endif