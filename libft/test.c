#include "libft.h"
#include <stdio.h>

int	main()
{
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;

	node1 = ft_lstnew("node1");
	node2 = ft_lstnew("node2");
	node3 = ft_lstnew("node3");

	node1->next = node2;
	node2->next = node3;

	t_list	*current = node1;
	t_list	*next_node;

	int	i = 0;
	while (i < 3)
	{
		printf("%s\n", (char *)current->content);
		next_node = current->next;
		current = next_node;
		i++;
	}

	ft_lstadd_front(&node1, ft_lstnew("new head"));
	// current = node1;
	// i = 0;
	// while (i < 4)
	// {
	// 	printf("%s\n", (char *)current->content);
	// 	next_node = current->next;
	// 	current = next_node;
	// 	i++;
	// }

	printf("lstsize function out = %d\n", ft_lstsize(node1));

	ft_lstadd_back(&node1, ft_lstnew("new last node"));

	printf("lstsize function out 2 = %d\n", ft_lstsize(node1));

	printf("last node = %s\n", (char *)ft_lstlast(node1)->content);

	char *str_arr[] = {"a1b1c1","a2b2c2"};
	char c[] = "aaa";
	char *ptr = (char *)c;

	ft_putchar_fd(*str_arr, 1);

	printf("\narray = %s\n", *str_arr);

	char tochange[] = "aaa";
	char *head = "bbb";
	ft_changechar(tochange);
	printf("changed ? %s\n", tochange);

	ft_changepointer(&head);
	printf("changed ? %s\n", head);
	return (0);
}
