#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
	int fd, status, child, pid;
	pid = fork();
	if(pid == 0){
	fd = open(argv[1],O_CREAT|O_TRUNC|O_WRONLY,0600);
	dup2(fd,1);
	close(fd);
	execvp(argv[2],&argv[2]);
	fprintf(stderr,"%s: execute fail\n",argv[1]);
	}else{
	child = wait(&status);
	printf("[%d] child process %d end\n",getpid(), child);
	}
}
