#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char* strArr[5];
char len[MAXLINE];

int main(){

	int i = 0;
	int num = 0;

	while(num == 5){
		scanf("%s", strArr[num]);
		num++;
	}
	
	for(i = 0; i < num; i++){
		for(j = 0; j < num; j++){
			if(strlen(strArr[i]) < strlen(strArr[j])){
				len = strArr[i];
				strArr[i] = strArr[j];
				strArr[j] = len;
			}			
		}
	}

	for(i = 0; i < num; i++){
		printf("%s\n", strArr[i]);
	}
	

	return 0;
}

