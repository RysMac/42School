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

	int 	pipe1[2];
	int		pipe2[2];
	int		nbr;
	int		sum;
	pipe(pipe1);
	pipe(pipe2);


	int id1 = fork();

	if (id1 == 0) {
		close(pipe2[0]);
		close(pipe2[1]);

		nbr = 10;
		write(pipe1[1], &nbr, sizeof(int));
		close(pipe1[1]);
	} else {
		close(pipe1[0]);
		close(pipe1[1]);

		nbr = 12;
		write(pipe2[1], &nbr, sizeof(int));
		close(pipe2[1]);


	}
	sum = 0;
	if (id1 != 0) {
		read(pipe1[0], &nbr, sizeof(int));
		close(pipe1[0]);
		sum += nbr;

		read(pipe2[0], &nbr, sizeof(int));
		close(pipe2[0]);
		sum += nbr;

		printf("task  %d...\n", sum);
	} else {
		close(pipe1[0]);
		close(pipe2[0]);
	}




	return (0);
}
