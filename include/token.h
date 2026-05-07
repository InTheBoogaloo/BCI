#ifndef TOKEN_H
#define TOKEN_H

typedef enum Token_type{
	IDENTIFIER,
	NUMBER,
	OPERATION,
	STRING,
	UNKNOWN
}Token_type;

typedef struct Token {
	struct Token *next;
	char *lexeme;
	Token_type type;
}Token;

Token* create_token();
void print_token(Token* t);

#endif
