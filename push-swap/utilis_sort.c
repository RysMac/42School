#include "push_swap.h"

static int get_position(t_stack *stack, int index)
{
	t_node *current = stack->top;
	int pos = 0;
	while (current)
	{
		if (current->index == index)
			return pos;
		current = current->next;
		pos++;
	}
	return -1;
}

static int get_max_index(t_stack *stack)
{
	t_node *current = stack->top;
	int max = current->index;
	while (current)
	{
		if (current->index > max)
			max = current->index;
		current = current->next;
	}
	return max;
}

void push_chunks(t_stack *a, t_stack *b, int chunk_count)
{
	int chunk_size = a->size / chunk_count;
	int i = 0;

	while (a->size > 0)
	{
		if (a->top->index < (i + 1) * chunk_size)
		{
			pb(a, b);
			if (b->top->index < i * chunk_size + (chunk_size / 2))
				rb(b);
		}
		else
			ra(a);
		if (b->size == (i + 1) * chunk_size)
			i++;
	}
}

void push_back_to_a(t_stack *a, t_stack *b)
{
	while (b->size > 0)
	{
		int max = get_max_index(b);
		int pos = get_position(b, max);

		if (pos <= b->size / 2)
		{
			while (b->top->index != max)
				rb(b);
		}
		else
		{
			while (b->top->index != max)
				rrb(b);
		}
		pa(a, b);
	}
}

void push_swap(t_stack *a, t_stack *b, int size)
{
	if (is_array_sorted(*a))
		return;

	push_chunks(a, b, 5);        // 5 chunks for 100 elements
	push_back_to_a(a, b);        // restore sorted
}
