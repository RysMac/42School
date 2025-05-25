#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrSize = sizeof(arr) / sizeof(int);
    int interval = arrSize / 4;
    int pipe1[2], pipe2[2], pipe3[2], pipe4[2];

    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);
    pipe(pipe4);

    int id1 = fork();
    if (id1 == 0) {
        int sum1 = arr[0] + arr[1];
        close(pipe1[0]);
        write(pipe1[1], &sum1, sizeof(int));
        close(pipe1[1]);
        exit(0);
    }

    int id2 = fork();
    if (id2 == 0) {
        int sum2 = arr[2] + arr[3];
        close(pipe2[0]);
        write(pipe2[1], &sum2, sizeof(int));
        close(pipe2[1]);
        exit(0);
    }

    int id3 = fork();
    if (id3 == 0) {
        int sum3 = arr[4] + arr[5];
        close(pipe3[0]);
        write(pipe3[1], &sum3, sizeof(int));
        close(pipe3[1]);
        exit(0);
    }

    int id4 = fork();
    if (id4 == 0) {
        int sum4 = arr[6] + arr[7] + arr[8] + arr[9];
        close(pipe4[0]);
        write(pipe4[1], &sum4, sizeof(int));
        close(pipe4[1]);
        exit(0);
    }

    close(pipe1[1]);
    close(pipe2[1]);
    close(pipe3[1]);
    close(pipe4[1]);

    int totalSum = 0, partialSum;
    read(pipe1[0], &partialSum, sizeof(int));
    totalSum += partialSum;
    read(pipe2[0], &partialSum, sizeof(int));
    totalSum += partialSum;
    read(pipe3[0], &partialSum, sizeof(int));
    totalSum += partialSum;
    read(pipe4[0], &partialSum, sizeof(int));
    totalSum += partialSum;

    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe3[0]);
    close(pipe4[0]);

    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Total sum: %d\n", totalSum);
    return 0;
}
