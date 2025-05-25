#include "push_swap.h"

int	assign_values(t_stack *stack, int *arr, int size)
{
	int index;
	int inner;
	int outer;
	int	max_index;
	t_node *node;

	outer = 0;
	max_index = 0;
	while (outer < size)
	{
		index = 0;
		inner = 0;
		while (inner < size)
		{
			if (arr[outer] > arr[inner])
				index++;
			inner++;
		}
		if (index > max_index)
			max_index = index;
		node = new_node(arr[outer]);
		node->index = index;
		add_back(stack, node);
		outer++;
	}
	return (max_index);
}

void push_swap(t_stack *stack_a, t_stack *stack_b, int max_bits, int size)
{
	int i;
	int j;

	j = 0;
	while (j < max_bits)
	{
		i = 0;
		while (i < size)
		{
			if (((stack_a->top->index >> j) & 1) == 0)
				pb(stack_a, stack_b);
			else
				ra(stack_a);
			i++;
		}
		while (stack_b->size > 0)
			pa(stack_a, stack_b);

		j++;
	}
}
