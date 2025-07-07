#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "lexer.h"

// INT_MAX = 2147483647

typedef struct{
	const char* buff;
	size_t bufflen;
	size_t pos;
} Lexer;

Lexer load(FILE *file){
	fseek(file,0,SEEK_END);
	long res = ftell(file);
	printf("[+] [DEBUG] ftell result: %ld\n",res);
	fclose(file);
	Lexer l = {malloc(res),res,0}; //Uncertainty with +1 for terminator
	return l;
}

void lex(const char* fn){ // TODO return token array pointer and size 
	FILE *file = fopen(fn,"r");
	Lexer lex = load(file); 

	if( lex.buff == NULL){
		printf("[+] [ERROR] Cannot allocate memory for %s\n",fn);
	}
	else{
		printf("[+] [DEBUG] Lexer's buff is: %p\n",lex.buff);
		do{
		int mode = 0; // Undefined mode
					  // 1 charmode, 2 symmode, 3 spacemode
		printf("[+] [DEBUG] lex.pos = %d\n",lex.pos);
		printf("[+] [DEBUG] Current char: %c\n",lex.buff[lex.pos]);
		
		//Lexing, assinging ints (with enum) as we go along

		lex.pos++;
		} while (lex.pos < lex.bufflen-1); //Doesn't read the terminator
										   //Perhaps it should to make tokenizing easier?
	}
}
