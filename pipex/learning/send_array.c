#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {

	// 2 processes
	// 1) Child process should generate random numbers and send them to the parent process
	// 2) Parent sum up all numbers and print the result
	int fd[2];
	if (pipe(fd) == -1) { return 2; }
	int pid = fork();
	if (pid == -1) { return 1;}

	if (pid == 0) {
		close(fd[0]);
		int n, i;
		int arr[10];

		srand(time(NULL));
		n = rand() % 10 + 1;
		for (i = 0; i < n; i++){
			arr[i] = rand() % 11;
			printf("Generated arr_i = %d\n", arr[i]);
		}
		if (write(fd[1], &n, sizeof(int) ) < 0 ) { return 3; }
		if (write(fd[1], arr, sizeof(int) * n) < 0 ) { return 3; }
		close(fd[1]);
	} else {
		close(fd[1]);
		int arr[10];
		int n, i, sum = 0;
		if (read(fd[0], &n, sizeof(int)) < 0 ) { return 3; };
		if (read(fd[0], arr, sizeof(int) * n) < 0) { return 3; };
		close(fd[0]);
		for (i = 0; i < n; i++) {
			sum += arr[i];
		}
		printf("Result is %d \n", sum);
		wait(NULL);
	}
	return (0);
}
