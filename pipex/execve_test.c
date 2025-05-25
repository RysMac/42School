#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	int fd[2];

	if (pipe(fd) < 0)
		return 1;

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		// Child: grep input from pipe
		close(fd[1]); // Close write end
		dup2(fd[0], STDIN_FILENO); // stdin <- pipe read
		close(fd[0]);

		char *argv[] = {"/bin/grep", "Hello", NULL};
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	else
	{
		// Parent: write to pipe
		close(fd[0]); // Close read end
		write(fd[1], "Hello World\nAnother line\n", 26);
		close(fd[1]); // Done writing

		int status;
		wait(&status);
		printf("Grep exited with status: %d\n", status);
	}
	return (0);
}


// int main(void)
// {
// 	pid_t pid;
// 	int fd_out;
// 	int fd_in;
// 	int fd[2];

// 	if (pipe(fd) < 0)
// 		return 1;

// 	char *argv[] = {"/bin/grep", "grep fsgf", NULL};

// 	// fd_out = open("end.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	// fd_in = open("start.txt", O_RDONLY, 0777);
// 	// dup2(fd_in, STDIN_FILENO);
// 	// dup2(fd_out, STDOUT_FILENO);

// 	pid = fork();
// 	if (pid == -1)
// 		return (-1);

// 	if (pid == 0)
// 	{
// 		if (execve(argv[0], argv, NULL) == -1)
// 		{
// 			printf("anything to print ? \n");
// 			fflush(stdout);
// 			exit(1);
// 		}
// 	}
// 	else
// 	{
// 		int status;
// 		wait(&status);
// 		printf("Done with execev................... %d \n", status);
// 	}
// 	return (0);
// }
