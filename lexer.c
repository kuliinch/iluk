#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "tokens.h"
#include "moods.h"

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

void eval(const char* unproc) {
	// TODO Tokenize and add token to array (TODO where?)
	printf("[+] [DEBUG] Eval has been called\n");
}

int typecheck(char* chr, int* m){
	char ch = *chr;
	//Use ctype.h 
	
	if(m == NULL){
		if(isalpha(ch)) return LETTER;
		else if(isdigit(ch)) return NUMBER;
		else if(ispunct(ch)) return SYMBOL;
		else if(isspace(ch)) return SPACE;
		return NOTHING;
	}
	int pmo = *m;
	if(pmo==OD) return OD;
	else if (pmo==OS) return OS;
	// TODO If the character is an escape character ('\') do something different
	if(ch=='\\'){
		if(pmo==OD) return ODE;
		else if(pmo==ODE) return ODE2;
		else if(pmo==ODE2) return ODE;
		else if(pmo==OS) return OSE;
		else if(pmo==OSE) return OSE2;
		else return 999;
	}
	else if(ch=='"'){
		if(pmo==OD) return CD;
		else if(pmo==ODE) return ODE2;
		else if(pmo==ODE2) return CD; 
		else return OD;
	}
	else if(ch=='\''){
		if(pmo==OS) return CS;
		else if(pmo==OSE) return OSE2;
		else if(pmo==OSE2) return CS; 
		else return OS;
	}
	return SYMBOL;
}	

void lex(const char* fn){ // TODO return token array pointer and size 
	FILE *file = fopen(fn,"r");
	Lexer lex = load(file); 

	if( lex.buff == NULL){
		printf("[+] [ERROR] Cannot allocate memory for %s\n",fn);
	}
	else{
		printf("[+] [DEBUG] Lexer's buff is: %p\n",lex.buff);
		char curr = lex.buff[0];
		char* currp = &curr;
		int mood = typecheck(currp, NULL); 
		int* moodp = &mood;
			// Mood keeps track of the previous char that has been shown
			// 0 = nothing, 1 = letter, 2 = number, 3 = symbol, 4 = space/nl
			// TODO add more types for escape sequences, literals, comments, etc.
		int type = 0;
		char last[100]; // WARNING Unprocessed token max size 
		int lastp = 0;
		do{
			curr = lex.buff[lex.pos];
			printf("[+] [DEBUG] lex.pos = %d\n",lex.pos);
			printf("[+] [DEBUG] Current char: %c\n",curr);
			
			//Lexing, assinging ints (with enum) as we go along
			/* If the character is of type X and mood has not changed, continue
			 * Once the mood has changed, evaluate the last token*/		
			type = typecheck(currp,moodp);

			printf("[+] [DEBUG] Curr type: %d\n",type);

			if(type==mood){
				last[lastp] = curr;
				lastp++;
			}
			else{
				printf("[+] [DEBUG] Mood change!, last = %s\n",last);
				// Evaluate and tokenize, then empty last
				last[lastp] = '\0';
				eval(last);
				last[0] = curr;
				last[1] = '\0';
				lastp = 1;
			}

			lex.pos++;
		} while(lex.pos < lex.bufflen); 
	}
}
