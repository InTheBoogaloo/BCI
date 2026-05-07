#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "include/list.h"

struct List{
	Token *head;
	Token *tail;
};

List* create_list(){
	List *l;
	l = (List*)malloc(sizeof(List));
	assert(l && "malloc failed"); 
	l->head = NULL;
	l->tail = l->head;
	return l;
}

int push_token(List *dst, Token *src){
	assert(dst || src);
	if(dst->head == NULL){
		dst->head = src;
		dst->tail = dst->head;
		return 0;
	}else{
		dst->tail->next = src;
		dst->tail = src;
		return 0;
	}
	return -1;
}

void print_list(List *l){
	printf("head: %p\ntail:%p\n", l->head, l->tail);
	assert(l);
	Token *aux = l->head;
	while(aux){
		print_token(aux);
		aux = aux->next;
	}
	return;
}

