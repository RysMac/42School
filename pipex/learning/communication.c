#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	// 5 => 5 * 4 = 20 => 20
	int p1[2]; // C => P
	int p2[2]; // P => C
	if (pipe(p1) == -1 || pipe(p2) == -1) { return 1; }
	int pid = fork();
	if (pid == -1) { return 2; }

	if (pid == 0) {
		printf("child process\n");
		int x;
		close(p1[0]);
		close(p2[1]);
		// get an integer number from file descriptor
		if (read(p2[0], &x, sizeof(x)) == -1) { printf("Read failed\n"); return 3; }
		printf("Received %d\n", x);
		x *= 4;
		if (write(p1[1], &x, sizeof(x)) == -1) { printf("Write failed\n"); return 4; }
		printf("Wrote %d\n", x);
		close(p1[1]);
		close(p2[0]);
	} else {
		// Parent process
		printf("Parent process\n");
		close(p1[1]);
		close(p2[0]);
		srand(time(NULL));
		int y = rand() % 10;
		if (write(p2[1], &y, sizeof(y)) == -1) { return 5; };
		printf("Parent wrote %d\n", y);
		if (read(p1[0], &y, sizeof(y)) == -1) {return 6;}
		printf("Parent reuslt is %d\n", y);
		close(p1[0]);
		close(p2[1]);
		wait(NULL);
	}
	return (0);
}
