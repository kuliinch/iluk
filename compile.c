/* TODO
 * 	- Create an elaborate CLI
 * 	- Introduce compiler settings and parameters
 */

#include <stdio.h>
#include <string.h>
#include "lexer.h"

int ilucheck(const char* fn){
	size_t len = strlen(fn);

	if( len > 5 && len < 100 && strcmp ( fn + len - 5, ".iluk" ) == 0 ) return 1;
	else return 0;
}

void compile(const char* fn){
	/* COMPILATION
	 * Lexer 
	 * Parser 
	 * Etc
	 */
	lex(fn);
}

int main(int argc, char* argv[]){
	printf("\n");
	char fns[100][100]; // Can only comile a maximum of 100 files of maximum 100 chars
	int j = 0;
	if(argc < 2) printf("[+] [INFO] No files given to compile\n");
	else{
		for(int i = 1; i < argc; i++){
			if(ilucheck(argv[i]) == 1){ // Also makes sure fn is under 100 chars
				FILE *file = fopen(argv[i],"r");
				if (file){
					strcpy(fns[j],argv[i]); 
					j++;
				}
				else printf("[+] [ERROR]%s either does not exist or cannot be read.\n",argv[i]);
				fclose(file);
			}
			else{
				printf("[+] [ERROR] %s isn't a .iluk file or name is too long (>100 chars).\n",argv[i]);
				break;
			}
		}
		for(int i = 0; i < j; i++) compile(fns[i]);
	}

	printf("Done!\n");
}
