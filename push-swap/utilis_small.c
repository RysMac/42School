#include "push_swap.h"

static int get_min_position(t_stack *a)
{
	t_node *cur = a->top;
	int min = cur->index;
	int pos = 0;
	int i = 0;

	while (cur)
	{
		if (cur->index < min)
		{
			min = cur->index;
			pos = i;
		}
		cur = cur->next;
		i++;
	}
	return pos;
}

void sort_3(t_stack *a)
{
	int first = a->top->nbr;
	int second = a->top->next->nbr;
	int third = a->top->next->next->nbr;

	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

void sort_4(t_stack *a, t_stack *b)
{
	int min_pos = get_min_position(a); // returns 0-based index of smallest element

	if (min_pos == 1)
		ra(a);
	else if (min_pos == 2)
	{
		ra(a);
		ra(a);
	}
	else if (min_pos == 3)
		rra(a);

	pb(a, b);           // push the smallest to B
	sort_3(a);          // sort remaining 3 elements
	pa(a, b);           // bring smallest back
}

void sort_5(t_stack *a, t_stack *b)
{
	int min_pos;

	// First smallest
	min_pos = get_min_position(a);
	if (min_pos == 1)
		ra(a);
	else if (min_pos == 2)
	{
		ra(a); ra(a);
	}
	else if (min_pos == 3)
	{
		rra(a); rra(a);
	}
	else if (min_pos == 4)
		rra(a);
	pb(a, b);

	// Second smallest
	min_pos = get_min_position(a);
	if (min_pos == 1)
		ra(a);
	else if (min_pos == 2)
	{
		ra(a); ra(a);
	}
	else if (min_pos == 3)
		rra(a);
	pb(a, b);

	sort_3(a);
	pa(a, b);
	pa(a, b);
}
