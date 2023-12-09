#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[])
{
	char **ptr;
	extern char **environ;
	
	if ((argc == 2 && strcmp(argv[1], "-e") == 0) || (argc == 3 && strcmp(argv[1], "-e") == 0)) {
		if (argc == 2) {
			for (ptr = environ; *ptr != 0; ptr++)
				printf("%s\n", *ptr);
		} else {
			char *env_var = getenv(argv[2]);
			if (env_var != NULL) {
				printf("%s=%s\n", argv[2], env_var);
			} else {
				printf("Environment variable '%s' not found.\n", argv[2]);
			}
		}
	} else if ((argc == 2 && strcmp(argv[1], "-i") == 0) || (argc == 2 && strcmp(argv[1], "-p") == 0)) {
		if (strcmp(argv[1], "-i") == 0) {
			printf("my process number : [%d]\n", getpid());
		} else {
			printf("my parent's process number : [%d]\n", getppid());
		}
	} else if (argc == 2 && strcmp(argv[1], "-u") == 0) {
		printf("My Realistic User ID : %d (%s)\n", getuid(), getpwuid(getuid())->pw_name);
		printf("My Valid User ID : %d (%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
	} else if (argc == 2 && strcmp(argv[1], "-g") == 0) {
		printf("My Realistic Group ID : %d (%s)\n", getgid(), getgrgid(getgid())->gr_name);
		printf("My Valid Group ID : %d (%s)\n", getegid(), getgrgid(getegid())->gr_name);
	} else {
		printf("Error:\n");
		printf("To display all environment variables : %s -e\n", argv[0]);
		printf("To display a specific environment variable : %s -e <ENV_VARIABLE>\n", argv[0]);
		printf("To display process ID : %s -i\n", argv[0]);
		printf("To display parent process ID : %s -p\n", argv[0]);
		printf("To display process user IDs : %s -u\n", argv[0]);
		printf("To display process group IDs : %s -g\n", argv[0]);
	}
	return 0;
}
