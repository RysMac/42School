#include "push_swap.h"

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
