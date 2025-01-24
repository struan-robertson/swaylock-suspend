#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void signal_handler(int signum) {
    if (signum == SIGUSR1) {
	if (fork() == 0) {
	    execl("/usr/bin/swaylockd", "swaylock", NULL);
	    perror("execl");
	    exit(1);
	}
    }
}

int main(void) {
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    for (;;) {
	pause();
    }

    return 0;
}
