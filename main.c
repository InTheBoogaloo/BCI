#include <stdio.h>
#include "include/tokenizer.h"
#include "include/list.h"


int main(){
	char *input = "ls mkdir hola = 1 -1";
	List *l = tokenize(input);
	print_list(l);
	return 0;
}
