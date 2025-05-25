
#include "push_swap.h"
#include <unistd.h>
#include <stdio.h>


int main()
{
	t_stack stack_a;

	int arr[] = {32, 2, 54 ,-65 ,68, -9890};
	int size = sizeof(arr) / sizeof(int);

	int curr_min = arr[0];
	int index = 0;
	int i = 0;
	int j = 0;
	while (j < size)
	{
		index = 0;
		i = 0;
		while (i < size)
		{
			if (arr[j] > arr[i])
				index++;
			i++;
		}
		printf("nbr : %d index: %d \n", arr[j], index);
		// assign index to number
		j++;
	}


	return (0);
}
