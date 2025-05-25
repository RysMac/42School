#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
	int pid = fork();
	if (pid == -1) { return 1; }

	if (pid == 0) {
		// child process
		int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777 );
		if ( file == -1 ) { printf("File errot."); return 2; };
		// int file_dup = dup(file); // creates another file descriptor, duplicates file and point to pingResults also... dup by itself does no do anything...

		printf("The fd to pingResults: %d\n", file);
		int file_dup2 = dup2(file, STDOUT_FILENO); // 1 - means STDOUT so dup2 creates file descr. duplicates file but replase STDOUT to file so changes the stream?
		printf("The duplicated fd: %d\n", file_dup2);
		close(file);

		int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
		if (err == -1) { printf("Could not find program to execute ! \n"); return 2; }
	} else {
		int wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus)){
			int statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0) {
				printf("Success ! \n");
			} else {
				printf("Failure \n");
			}
		}
		printf("Some postprocessing goes here! \n");
	}


	return (0);
}
