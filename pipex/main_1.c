#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *const argv[] = { "ls", "-l", NULL };  // Run "wc -w file.txt"
    char *const envp[] = { "/bin/ls", NULL };

	execve("ls", argv, envp);
	perror("Error executing execve");
    // if (execve("/bin/echo", argv, envp) == -1) {

    //     return 1;
    // }

    printf("You will never see this line!\n");
    return 0;
}
