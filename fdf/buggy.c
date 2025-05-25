#include <stdio.h>

int sum(int *arr, int size)
{
    int total = 0;
    for (int i = 0; i <= size; i++)  // ❌ bug: should be i < size
        total += arr[i];
    return total;
}

int main(void)
{
    int nums[] = {1, 2, 3, 4, 5};
    int result = sum(nums, 5);
    printf("Sum is: %d\n", result);
    return 0;
}
