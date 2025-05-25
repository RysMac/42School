#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {
	int fd[2];
	if (pipe(fd) == -1) { return 1; }
	int pid = fork();
	if ( pid == -1) { return 2; }

	if (pid == 0) {
		// child process
		close(fd[0]);
		char str[200];
		printf("Input string: ");
		fgets(str, 200, stdin);
		str[strlen(str) -1] = '\0';

		int n = strlen(str) + 1;
		if (write(fd[1], &n, sizeof(int)) < 0) { return 4; }
		if (write(fd[1], str, strlen(str) + 1 ) < 0) { return 3; }
		close(fd[1]);

	} else {
		// parent process
		close(fd[1]);
		char str[200];
		int n;
		read(fd[0], &n, sizeof(int));
		read(fd[0], str, sizeof(char) * n);
		close(fd[0]);
		wait(NULL);
		printf("%s \n", str);
	}

	return 0;
}
