#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	struct stat buf;

	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[1]);
		if (lstat(argv[1], &buf) < 0) {
			perror("istat()");
			continue;
		}

		if (S_ISREG(buf.st_mode))
			printf("%s \n", "general file");
		if (S_ISDIR(buf.st_mode))
			printf("%s \n", "directory");
		if (S_ISCHR(buf.st_mode))
            printf("%s \n", "character system file");
		if (S_ISBLK(buf.st_mode))
            printf("%s \n", "block system file");
		if (S_ISFIFO(buf.st_mode))
            printf("%s \n", "FIFO file");
		if (S_ISLNK(buf.st_mode))
            printf("%s \n", "symbolic link");
		if (S_ISSOCK(buf.st_mode))
            printf("%s \n", "socket");
	}
	exit(0);
}
