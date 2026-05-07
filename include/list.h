#ifndef LIST_H
#define LIST_H
#include "token.h"

typedef struct List List;

List* create_list();
int push_token(List *dst, Token *src);
void print_list(List *l);
void destroy_list(List *l);

#endif
