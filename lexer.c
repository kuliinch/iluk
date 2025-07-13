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
	fclose(file);
	Lexer l = {malloc(res),res,0}; 
	return l;
}

void eval(const char* unprocessed_t,const int* size, const int* previous_mood) {
	// TODO Tokenize and add token to array (TODO where?)
	printf("[+] [DEBUG] Eval has been called\n");
	int n = *size;
	printf("[+] [DEBUG] Last buffer (until \\0):\n\t");
	for(int i = 0; i < n; i++) printf("%c",*(unprocessed_t+i));
	printf("\n");
}

int typecheck(char* char_p, int* mood_p){
	char ch = *char_p; int previous_mood = *mood_p;
	printf("[+] [DEBUG]\n\t%c %p\n\t%d %p\n",ch,char_p,previous_mood,mood_p);
	//TODO fix issue when mutliple symbols are together, such as a quote inside a parenthesis	
	switch(previous_mood){
		case QUOTE:
			if(ch=='\\'){
				*mood_p = QUOTE_ESCAPE; 
				return QUOTE_ESCAPE;
			}
			else if(ch=='"'){
				*mood_p = QUOTE_CLOSE;
				return QUOTE_CLOSE;
			}
		case CHAR:
			if(ch=='\\'){
				*mood_p = CHAR_ESCAPE;
				return CHAR_ESCAPE;
			}
			else if(ch=='\''){
				*mood_p = CHAR_CLOSE;
				return CHAR_CLOSE;
			}
		case QUOTE_ESCAPE:
			*mood_p = QUOTE_ESCAPED;
			return QUOTE_ESCAPED;
		case CHAR_ESCAPE:
			*mood_p = CHAR_ESCAPED;
			return CHAR_ESCAPED;
		case QUOTE_ESCAPED:
			*mood_p = QUOTE;
			return QUOTE;
		case CHAR_ESCAPED:
			*mood_p = CHAR_CLOSE;
			return CHAR_CLOSE;
		default:
			if(isalpha(ch)) return ALPHA;
			else if(isdigit(ch)) return DIGIT;
			else if(ispunct(ch)) return SYMBOL;
			else if(isspace(ch)) return SPACE;
			else return NOTHING;
		}
	}

void lex(const char* fn){ // TODO return token array pointer and size 
	FILE *file = fopen(fn,"r");
	Lexer lex = load(file); 

	if( lex.buff == NULL){
		printf("[+] [ERROR] Cannot allocate memory for %s\n",fn);
	}
	else{
		char current; 
		char* current_pointer = &current;
		int mood;
		int* mood_pointer = &mood;
		mood = typecheck(current_pointer,mood_pointer);
		int type; 
		char last[100]; // Max unprocessed token size
		int lastp = 0;
		int* lastpp = &lastp;
		do{
			current = lex.buff[lex.pos];
			printf("[+] [DEBUG] lex.pos = %d\n",lex.pos);
			printf("[+] [DEBUG] Current char: %c\n",current);
			
			type = typecheck(current_pointer,mood_pointer);

			printf("[+] [DEBUG] Curr type: %d\n",type);

			if(type==mood){
				last[lastp] = current;
				lastp++;
			}
			else{
				last[lastp] = '\0';
				eval(last,lastpp,mood_pointer);
				last[0] = current;
				lastp = 1;
			}
			mood = type;	
			lex.pos++;
		} while(lex.pos < lex.bufflen); 
	}
}
