#include "push_swap.h"

void	error_and_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	fill_array(int *array, char **argv, int size)
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < size)
	{
		array[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	i = 0;
	while (i < size)
	{
		j = i + 1;
		tmp = array[i];
		while (j < size)
		{
			if (tmp == array[j])
				error_and_exit();
			j++;
		}
		i++;
	}
	return ;
}

int	is_array_sorted(t_stack stack)
{
	int i;
	t_node *node;

	node = stack.top;
	while (node->next)
	{
		if (node->index > node->next->index)
			return (0);
		node = node->next;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long	nbr = 0;
	int		sign = 1;

	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : 1;
	if (!*str)
		error_and_exit(); // empty string after sign

	while (*str)
	{
		if (*str < '0' || *str > '9')
			error_and_exit(); // non-digit char
		nbr = nbr * 10 + (*str - '0');
		if ((sign == 1 && nbr > 2147483647) || (sign == -1 && -nbr < -2147483648))
			error_and_exit(); // overflow
		str++;
	}
	return ((int)(nbr * sign));
}

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
