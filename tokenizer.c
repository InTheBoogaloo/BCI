#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "include/token.h"
#include "include/tokenizer.h"

Token* get_next_token(const char *input);

Token* get_next_token(const char *input) {
	assert(input && "no input");
	typedef enum{
		START,
		ERROR,
		IN_ID,
		IN_NUM,
		IN_STRING,
		FINAL_ID,
		FINAL_NUMBER,
		FINAL_OP,
		FINAL_STR
	}State;

	Token *t;
	State s = START;
	const char* aux = input;

	while(1) {
		switch(s) {
		case START:
			if(isalpha(*aux)){
				s = IN_ID;
				break;
			}else if(strlen(aux)==1 && *aux == '=' || *aux == '+' || *aux == '-' || *aux == '/'){
				s = FINAL_OP;
				break;
			}else if(isdigit(*aux)){
				s = IN_NUM;
				break;
			}else if(*aux == 39){
				s = IN_STRING;
				aux++;
				break;
			}else{
				s = ERROR;
				break;
			}

		case ERROR:
			t = create_token();
			t->lexeme = strdup(input);
			t->type = UNKNOWN;
			return t;

		case IN_ID:
			if(*aux == 0){
				s = FINAL_ID;
				break;
			}else if(!isalpha(*aux)){
				s = ERROR;
				break;
			}else{
				aux++;
				break;
			}

		case IN_NUM:
			if(*aux == 0){
				s = FINAL_NUMBER;
				break;
			}else if(!isdigit(*aux)){
				s = ERROR;
				break;
			}else{
				aux++;
				break;
			}
		case IN_STRING:
			if(*aux == 39){
				s = FINAL_STR;
				break;
			}else if(*aux == 0){
				s = ERROR;
				break;
			}else{
				aux++;
				break;
			}
			break;
		case FINAL_STR:
			t = create_token();
			t->lexeme = strdup(input);
			t->type = STRING;
			return t;

		case FINAL_NUMBER:
			t = create_token();
			t->lexeme = strdup(input);
			t->type = NUMBER;
			return t;
		case FINAL_ID:
			t = create_token();
			t->lexeme = strdup(input);
			t->type = IDENTIFIER;
			return t;
		case FINAL_OP:
			t = create_token();
			t->lexeme = strdup(input);
			t->type = OPERATION;
			return t;
		}
	}
	return NULL;
}

void clean_buffer(char buffer[100]){
	for(int i = 0; i < 100; i++){
		buffer[i] = 0;
	}
}

List* tokenize(const char* input){
	assert(input);

	List* l = create_list();
	const char* str = input;
	char buffer[1000];
	int i = 0;
  
	while(1){
		if(*str == 10) {
			Token* t = get_next_token(buffer);
			push_token(l,t);
			i = 0;
			clean_buffer(buffer);
			str++;
		}
		if(*str == 32) {
			buffer[i] = '\0';
			Token* t = get_next_token(buffer);
			push_token(l,t);
			str++;
			i= 0;
			clean_buffer(buffer);
		}
		if(*str == 0){
			Token* t = get_next_token(buffer);
			push_token(l,t);
			i = 0;
			return l;
		}if(*str == 39){
			int flag = 1;
			while(flag){
				buffer[i] = *str;
				i++; str++;
				if(*str == 39) flag = 0;
			}
		}
		buffer[i] = *str;
		str++;
		i++;
	}
	return NULL;
}
