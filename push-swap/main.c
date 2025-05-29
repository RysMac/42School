#include "push_swap.h"

int main(int argc, char *argv[])
{
	// check if it is already sorted
	// 4 args
	// 5 args
	int arr[argc - 1];
	t_stack stack_a;
	t_stack stack_b;
	t_node *node;
	int max_index = 0;

	// initialization
	stack_a.top = NULL;
	stack_a.size = 0;
	stack_b.top = NULL;
	stack_b.size = 0;

	// printf("array length = %d \n", argc - 1);
	fill_array(arr, argv, argc - 1);
	int i = 0;
	// while (i < argc - 1)
	// {
	// 	printf("array %d = %d \n", i, arr[i]);
	// 	i++;
	// }

	max_index = assign_values(&stack_a, arr, argc - 1);

	int	val = is_array_sorted(stack_a);
	// printf("is sorted : %d \n", val);
	if (val == 1)
		return 0;

	// printf("max bits is : %d \n", max_bits);

	if (stack_a.size <= 3)
		sort_3(&stack_a);
	else if (stack_a.size == 4)
		sort_4(&stack_a, &stack_b);
	else if (stack_a.size == 5)
		sort_5(&stack_a, &stack_b);
	else
		push_swap(&stack_a, &stack_b, argc - 1);

	// print results
	i = 0;
	node = stack_a.top;
	while (i < argc - 1)
	{
		printf("A node value: %d index: %d\n", node->nbr, node->index);
		node = node->next;
		i++;
	}
	ft_lstclear(&stack_a);
	return (0);
}
