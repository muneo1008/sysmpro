#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd;
	int totalLine = 0;
	char savedText[10][100];
	int i = 0, j = 0;
	char buf, c;
	char *num;

	if (argc < 2){
		fprintf(stderr, "How to use : %s file1\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1],O_RDONLY)) == -1){
		printf("File Open Error\n");
	}else{
		printf("File Read Success\n");
	}
	
	while(( c = read(fd, &buf, 1)) > 0){
		savedText[i][j] = buf;
		j++;
		if(buf == '\n'){
			i++;
			j = 0;
		}
	}
	close(fd);

	totalLine = i;
	printf("Total Line : %d\n",totalLine);
	printf("You can choose 1 ~ %d Line\n",totalLine);
	printf("Pls 'Enter' the line to select : ");
	scanf("%s",num);

	if (!strcmp(num, "*")){
		for (int k = 0; k < totalLine; k++){
			printf("%s", savedText[k]);
		}
	}

	exit(0);
}
