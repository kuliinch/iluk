#include <stdio.h>
#include <strings.h>
#include "lexer.h"

// INT_MAX = 2147483647

int nexttoken(char* p){
	/*
	 * Looks ahead and tries to find the next token
	 * Use case example: seeing if a variable is being defined without an identifier
	 * Expects the next token to be separated from the token at p with either a newline or whitespace
	 */ 

}

/*
 * Loop through every character in the file
 * When we encounter a space or a "mood change"
 * 	I.E we go from reading words to reading symbols (or vice-versa)
 * We analyse the word and see if its a keyword or we assing it a new token
 * Add token to array (?)
 */
void lex(const char* fn){
	FILE *file = fopen(fn,"r");
	int c

	while ( c = fgetc(*file) != EOF ){
			
	}
}
