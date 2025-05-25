#include "push_swap.h"

int main(int argc, char *argv[])
{
	int i = 0;
	t_stack stack_a;
	t_stack stack_b;
	t_node *current;

	stack_a.top = new_node(i++);
	stack_a.size = 1;

	current = stack_a.top;
	while (i < 5)
	{
		add_front(&stack_a, new_node(i));
		add_back(&stack_a, new_node(i + 10));
		i++;
	}
	// printf("top node %d \n", stack_a.top->nbr);
	sa(&stack_a);
	sb(&stack_a);
	ss(&stack_a, &stack_a);

	i = 0;
	while (i < 4)
	{
		pb(&stack_a, &stack_b);
		i++;
	}

	ra(&stack_a);
	rb(&stack_b);

	current = stack_a.top;
	i = 0;
	while (current)
	{
		printf("stack a node value = %d\n", current->nbr);
		current = current->next;
		i++;
	}

	current = stack_b.top;
	i = 0;
	while (current)
	{
		printf("stack b node value = %d\n", current->nbr);
		current = current->next;
		i++;
	}

	printf("top node %d \n", stack_a.top->nbr);
	printf("the size %d \n", stack_a.size);

	ft_lstclear(&(stack_a));
	return (0);
}
