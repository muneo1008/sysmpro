#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100

int main(int argc, char *argv[]){
	FILE *fp;
	char *c;
	int fileIndex = 1, i = 0;
	char buffer[MAXLINE];

	if(argc < 2){
		fprintf(stderr, "How to use : %s [string] file",argv[0]);
		exit(0);
	}else if(argc == 3){
		fileIndex++;
		fp = fopen(argv[fileIndex], "r");
		while(fgets(buffer, MAXLINE, fp) != NULL){
			if(strstr(buffer, argv[1]) != NULL){
				printf("%s", buffer);
			}
		}
	}else if(argc == 2){
		fp = fopen(argv[fileIndex], "r");
		while(fgets(buffer, MAXLINE, fp) != NULL){
			printf("%s", buffer);
			i++;
			if (i == 2) break;
		}
	}

	fclose(fp);
	return 0;
}
