#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "include/token.h"

Token* create_token();

void print_token(Token* t){
	printf("current token:%p\n", t);
	printf("next:%p\n", t->next);
	printf("lexeme:%s\n", t->lexeme);
	printf("type:%i\n", t->type);
}

Token* create_token(){
	Token *t;
	t = (Token*)malloc(sizeof(Token));
	assert(t && "no enought memory");
	t->next = NULL;
	t->lexeme = NULL;
	t->type = UNKNOWN;
	return t;
}
