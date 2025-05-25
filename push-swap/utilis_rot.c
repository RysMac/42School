#include "push_swap.h"

void rotate(t_stack *stack)
{
	t_node *first;
	t_node *current;

	if (!stack || !stack->top || !stack->top->next)
		return ;

	first = stack->top;
	stack->top = first->next;
	first->next = NULL;

	current = stack->top;
	while (current->next)
	{
		current = current->next;
	}
	current->next = first;
}

void ra(t_stack *a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

void rb(t_stack *b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

void rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}
