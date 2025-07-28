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

typedef struct{
	const char* lexeme;
	const int token;
} Token;

Lexer load(FILE *file){
	fseek(file,0,SEEK_END);
	long res = ftell(file);
	fclose(file);
	Lexer l = {malloc(res),res,0}; 
	return l;
}

void eval(const char* lexeme, const Token* token_buff, const size_t token_index) {
	/* TOKENIZER
	 * Uses the same buffer as the file to store the tokens
	 * Needs a hashmap for variable names
	 */
	printf("[+] [DEBUG] eval called! Evaluating --%s--\n",lexeme);
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
						switch(previous_mood){
							case SYMBOL:
								return SYMBOL_ALT;
							case SYMBOL_ALT:
								return SYMBOL;
							default:
								return SYMBOL;
						}
				}
			}
			else if(isspace(ch)) return SPACE;
			else return NOTHING;
		}
	}

void lex(const char* fn){ // TODO return token array pointer and size 
	FILE *file = fopen(fn,"r");
	Lexer lex = load(file); 
	Token* token_buff = malloc(sizeof(Token)*100);
	size_t token_pos = 0;
	char current; char* current_pointer = &current;
	int mood; int* mood_pointer = &mood;
	int type; 
	char last[100]; // Max unprocessed token size
	int lastp = 0; 

	if( lex.buff != NULL && token_buff != NULL){
		mood = typecheck(current_pointer,mood_pointer);
		do{
			current = lex.buff[lex.pos];
			type = typecheck(current_pointer,mood_pointer);
			if(type==mood){
				last[lastp] = current;
				lastp++;
			}
			else{
				last[lastp] = '\0';
				eval(last,token_buff,token_pos);
				token_pos++;
				last[0] = current;
				lastp = 1;
			}
			mood = type;	
			lex.pos++;
		} while(lex.pos < lex.bufflen); 
	}
	else{
		printf("[+] [ERROR] Cannot allocate memory.");
	}
}
