#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESS_NUM 3


int main(int argc, char* argv[]) {
	int pids[PROCESS_NUM];
	int pipes[PROCESS_NUM + 1][2];
	int i;

	for (i = 0; i < PROCESS_NUM + 1; i++) {
		if (pipe(pipes[i]) == -1) { printf("Error with creating pipes. \n"); return 1; }
	}

	for (i = 0; i < PROCESS_NUM; i++) {

		pids[i] = fork();
		if (pids[i] == -1) {
			printf("Error with creating processes \n");
			return 2;
		}
		if (pids[i] == 0) {
			// Child process
			return 0;
		}
	}

	for (i = 0; i < PROCESS_NUM; i++) {
		wait(NULL);
	}


	return 0;
}
