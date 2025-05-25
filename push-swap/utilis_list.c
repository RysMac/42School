#include "push_swap.h"

void	ft_lstclear(t_stack *stack)
{
	t_node  *current;
	t_node  *next;

	if (!stack || !(stack->top))
		return;
	current = stack->top;
	while (current)
	{
			next = current->next;
			free(current);
			current = next;
	}
	stack->top = NULL;
	stack->size = 0;
}

t_node *new_node(int nbr)
{
	t_node *new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return NULL;
	new->nbr = nbr;
	new->index = 0;
	new->next = NULL;
	return (new);
}

void add_back(t_stack *stack, t_node *node)
{
	t_node *current;

	if (!stack || !node)
		return ;

	// node->next = NULL; not needed
	if (stack->top == NULL)
	{
		stack->top = node;
		stack->size = 1;
		return ;
	}
	current = stack->top;
	while (current->next)
	{
		current = current->next;
	}
	current->next = node;
	stack->size++;
}

void add_front(t_stack *stack, t_node *node)
{
	t_node *current;

	if (!stack || !node)
		return ;

	current = stack->top;
	stack->top = node;
	stack->size++;
	stack->top->next = current;
}
