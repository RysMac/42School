#include "push_swap.h"

static void swap_top(t_stack *stack)
{
	t_node *first_node;
	t_node *second_node;

	if (!stack || !(stack->top) || stack->size < 2)
		return ;
	first_node = stack->top;
	second_node = stack->top->next;

	first_node->next = second_node->next;
	second_node->next = first_node;
	stack->top = second_node;
}

void sa(t_stack *a)
{
	swap_top(a);
	write(1, "sa\n", 3);
}

void sb(t_stack *b)
{
	swap_top(b);
	write(1, "sb\n", 3);
}

void ss(t_stack *a, t_stack *b)
{
	swap_top(a);
	swap_top(b);
	write(1, "ss\n", 3);
}
