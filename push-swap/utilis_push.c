#include "push_swap.h"

static void push(t_stack *dest, t_stack *src)
{
	t_node *top_src;

	if (!src || !src->top)
		return ;

	top_src = src->top;
	src->top = top_src->next;
	src->size--;

	top_src->next = dest->top;
	dest->top = top_src;
	dest->size++;
}

void pa(t_stack *a, t_stack *b)
{
	push(a, b);
	write(1, "pa\n", 3);
}

void pb(t_stack *a, t_stack *b)
{
	push(b, a);
	write(1, "pb\n", 3);
}
