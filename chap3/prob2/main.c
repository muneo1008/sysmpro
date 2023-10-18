#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char strArr[5][MAXLINE];
void copy(char from[], char to[]);

int main(){
	
	int max = 0;
	
	while(max < 5){
		fgets(strArr[max], MAXLINE, stdin);
		max++;
	}
	
	for(int j = 0; j < 4; j++){
	    for(int k = 0; k < 4 - j; k++){
		    if(strlen(strArr[k]) < strlen(strArr[k+1])){
			copy(strArr[k], line);
			copy(strArr[k+1], strArr[k]);
			copy(line, strArr[k+1]);
		     }

	    }
	}

	puts("");
	for(int i = 0; i < 5; i++){
		printf("%s",strArr[i]);
	}




	return 0;
}
