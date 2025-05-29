#include "push_swap.h"

void rev_rotate(t_stack *stack)
{
	t_node *prev;
	t_node *last;

	if (!stack || !stack->top || !stack->top->next)
		return ;

	prev = NULL;
	last = stack->top;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	if (prev)
		prev->next = NULL;
	last->next = stack->top;
	stack->top = last;
}

void rra(t_stack *a)
{
	rev_rotate(a);
	write(1, "rra\n", 4);
}

void rrb(t_stack *b)
{
	rev_rotate(b);
	write(1, "rrb\n", 4);
}

void rrr(t_stack *a, t_stack *b)
{
	rev_rotate(a);
	rev_rotate(b);
	write(1, "rrr\n", 4);
}
