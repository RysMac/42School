#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void handle_sigtstp(int sig) {
	printf("Stop nor allowed \n");
}

void handle_sigcount(int sig) {
	printf("Input number: ");
	fflush(stdout);
}

int main(int arg, char* argv[]) {
	struct sigaction sa;
	sa.sa_handler = &handle_sigcount;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGCONT, &sa, NULL);

	int x;
	printf("Input number:  ");
	scanf("%d", &x);
	printf("Result %d * 5 = %d \n", x, x * 5);

	return 0;
}
