#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

int line = 1; // 파일 여려개를 같이 출력해도 라인번호가 같이 적용되게 하려고 전역로 설정했고 따로 적용
	      // 하려면 printLineNum안에 넣으면 됩니다.

void printLineNum(FILE *fp) {
    	char buffer[MAXLINE];
    	while (fgets(buffer, MAXLINE, fp) != NULL) {
        	printf("%2d| %s", line, buffer);
		line++;
    	}
}

int main(int argc, char *argv[]) {

    	char c;
	int useLineNum = 0;
	int fileIndex = 1;

    	if (argc < 2) {
        	fprintf(stderr, "How to use : %s [-n] file1 [file2 ...]\n", argv[0]);
        	exit(1);
    	}

    	if (strcmp(argv[1], "-n") == 0) {
        	useLineNum = 1;
        	fileIndex++;
    	}

    	for (int i = fileIndex; i < argc; i++) {
		FILE *fp;
	    	if ((fp = fopen(argv[i], "r")) == NULL) {
			fprintf(stderr, "Error: Cannot open file %s\n", argv[i]);
            		continue;
        	}
        	if (useLineNum) {
            		printLineNum(fp);
        	} else {
            		while ((c = getc(fp)) != EOF) {
                	putc(c, stdout);
            		}
        	}

        fclose(fp);
    	}

    return 0;
}
