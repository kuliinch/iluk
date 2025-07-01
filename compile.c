#include <stdio.h>

//#include "lexer.h"

void verif(const char* fns[]){
	// Verifies the existence of the files

	//Look for file

}

int main(int argc, char* argv[]){
	/*
	 * Verify that files have been mentioned
	 * Check to see if those files exist in that directory AND that they have the correct file extension (.ulik)
	 * Compile the files into one object file
	 */
	char* fns[100];
	if(argc < 2) printf("[+] WARNING No files detected! ");
	else{
		for(int i = 1; i < argc; i++){
			if(1==0 /*argv[i] ends with .ulik */){
			}
			else printf("[+] WARNING %s isn't a .ulik file!\n",argv[i]);
		}
	}
}
