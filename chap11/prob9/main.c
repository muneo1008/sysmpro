#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void alarmHandler(int signo);

int main() {
    int sec = 1;

    struct sigaction sa;
    sa.sa_handler = alarmHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    alarm(5);
    while (1) {
        sleep(1);
        printf("%d second\n", sec++);
    }
    printf("Run error\n");
}

void alarmHandler(int signo) {
    printf("Wake up\n");
    exit(0);
}
