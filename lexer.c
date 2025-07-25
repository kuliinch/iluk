#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "tokens.h"
#include "moods.h"

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
	int n = *size;
	printf("\t[+] [DEBUG] eval called! \n\t----\n\t");
	for(int i = 0; i < n; i++) printf("%c",*(unprocessed_t+i));
	printf("\n\t----\n");
}

static inline int setmood(int* mood_p, int state) {
    *mood_p = state;
    return state;
}

int typecheck(char* char_p, int* mood_p){
	char ch = *char_p; int previous_mood = *mood_p;
	//TODO fix issue when mutliple symbols are together, such as a quote inside a parenthesis	
	switch(previous_mood){
		case QUOTE:
			switch(ch){
				case '\\':
					*mood_p = QUOTE_ESCAPE;
					return QUOTE_ESCAPE;
				case '"':
					*mood_p = QUOTE_CLOSE;
					return QUOTE_CLOSE;
				default: return QUOTE;
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
			if(ch=='"'){
				*mood_p = QUOTE_CLOSE;
				return QUOTE_CLOSE;
			}
			*mood_p = QUOTE;
			return QUOTE;
		case CHAR_ESCAPED:
			*mood_p = CHAR_CLOSE;
			return CHAR_CLOSE;
		default:
			if(isalpha(ch)) return ALPHA;
			else if(isdigit(ch)) return DIGIT;
			else if(ispunct(ch)){
				switch (ch){
					case '"':
						return QUOTE;
					case '\'':
						return CHAR;
					default:
						return SYMBOL;
				}
			}
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
			type = typecheck(current_pointer,mood_pointer);

			printf("[+] [DEBUG] Current char and type:\t%c\t%d\n",current,type);
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
