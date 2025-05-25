#include "push_swap.h"

int main(int argc, char *argv[])
{
	// int arr[] = {32, 2, 54 ,-65 ,68, -9890, 443, 4, 1, 5, 123, 4343, 2345, 50, 10, 657};
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	int size = sizeof(arr) / sizeof(int);
	printf("size %d \n", size);
	t_stack stack_a;
	t_stack stack_b;
	t_node *node;
	int max_index = 0;

	stack_a.top = NULL;
	stack_a.size = 0;
	stack_b.top = NULL;
	stack_b.size = 0;

	max_index = assign_values(&stack_a, arr, size);
	printf("max index is : %d \n", max_index);
	int max_bits = 0;
	while ((max_index >> max_bits) != 0)
		max_bits++;
	printf("max bits is : %d \n", max_bits);

	push_swap(&stack_a, &stack_b, max_bits, size);

	int i = 0;
	node = stack_a.top;
	while (i < size)
	{
		printf("A node value: %d index: %d\n", node->nbr, node->index);
		node = node->next;
		i++;
	}
	node = stack_b.top;
	while (node)
	{
		printf("B node value: %d index: %d\n", node->nbr, node->index);
		node = node->next;
	}
	return (0);
}
