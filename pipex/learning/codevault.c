#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	//printf("this is the lecture from CodeVault \n");

	// fork creates new process - called child process
	// id from a child process is going to be always 0 !!!
	// every child process has id=0 even if there are more than one
	// pipe is for saving memory, you can transfer data beteen processes, as input an array of two integers are needed, file descriptors are needed

	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int arrSize = sizeof(arr) / sizeof(int);
	int interval = arrSize / 4;
	int start, end;

	int pipe1[2];
	if (pipe(pipe1) == -1)	{
		printf("pipe error\n");
		return 1;
	}
	int idf1 = fork();
	int idf2 = fork();
	if (idf1 == -1 || idf2 == -1){
		return (printf("fork1 error"), 2);
	}

	if (idf1 == 0 && idf2 == 0){
		start = 0;
		end = interval;
		printf("start = %d \n", start);
		printf("end = %d \n", end);
	} else if (idf1 == 0 && idf2 != 0) {
		start = interval;
		end = interval * 2;
		printf("start = %d \n", start);
		printf("end = %d \n", end);
	} else if (idf1 != 0 && idf2 == 0) {
		start = interval * 2;
		end = interval * 3;
		printf("start = %d \n", start);
		printf("end = %d \n", end);
	} else {
		start = interval * 3;
		end = arrSize;
		printf("start = %d \n", start);
		printf("end = %d \n", end);
	}

	int sum = 0;
	for (int i = start; i < end; i++){
		sum += arr[i];
	}
	printf("Calculated partial sum: %d \n", sum);

	// if (id == 0){
	// 	close(fd[0]);
	// 	write(fd[1], &sum, sizeof(sum));
	// 	close(fd[1]);
	// } else {
	// 	int sumChild;
	// 	close(fd[1]);
	// 	wait(NULL);
	// 	read(fd[0], &sumChild, sizeof(sumChild));
	// 	close(fd[0]);
	// 	sum += sumChild;
	// }

	// printf("Calculated partial sum: %d \n", sum);

	// int fd[2];
	// // fd[0] - file descriptor for read
	// // fd[1] - file descriptor for write
	// if (pipe(fd) == -1)
	// {
	// 	printf("An error occured with opening the pipie \n");
	// 	return 1;
	// }
	// int id = fork();
	// if (id ==0)
	// {
	// 	close(fd[0]);
	// 	int x;
	// 	printf("Input a number: ");
	// 	scanf("%d", &x);
	// 	if (write(fd[1], &x, sizeof(int)) == -1)
	// 	{
	// 		printf("bad behaviour of write in the child process");
	// 		return (2);
	// 	}
	// 	close(fd[1]);
	// }
	// else
	// {
	// 	close(fd[1]);
	// 	wait(NULL);
	// 	int y;
	// 	read(fd[0], &y, sizeof(int));
	// 	close(fd[0]);
	// 	printf("Got from child process %d \n", y);
	// }

	/* ************************************************************* */
	// int id1 = fork();
	// int id2 = fork();
	// if (id1 == 0){
	// 	if (id2 == 0) {
	// 		printf("We are in the child of a child process\n");
	// 	} else {
	// 		printf("We are in the child of the parent process\n");
	// 	}
	// } else {
	// 	if (id2 == 0) {
	// 		printf("We are in the second child of the parent\n");
	// 	} else {
	// 		printf("We are in the parent process. \n");
	// 	}
	// }
	// while (wait(NULL) != -1 || errno != ECHILD) {
	// 	printf("Waited for a child to finish \n");
	// }

	/* ************************************************************* */
	// int id = fork();
	// if (id == 0)
	// 	sleep(2);

	// printf("Get the current ID %d and parent ID %d \n", getpid(), getppid() );

	// int res = wait(NULL);
	// if (res == -1)
	// 	printf("No children to wait for \n");
	// else
	// 	printf("%d finished execution", res);
	/* ************************************************************* */
	// printf("Get the parent ID %d \n", getppid() );

	// int n;
	// if (id == 0)
	// 	n = 1;
	// else
	// {
	// 	wait(NULL);
	// 	n = 6;
	// }

	// int i;
	// for (i = n; i < n + 5; i++)
	// {
	// 	printf("%d  ", i);
	// 	fflush(stdout);
	// }
	// printf("\n");
	return (0);
}
