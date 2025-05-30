#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>


typedef struct s_node
{
	int nbr;
	int index;
	struct s_node *next;
	/* data */
}	t_node;

typedef struct s_stack
{
	t_node *top;
	int size;
} t_stack;


void	ft_lstclear(t_stack *stack);
t_node *new_node(int nbr);
void add_back(t_stack *stack, t_node *node);
void add_front(t_stack *stack, t_node *node);

void sa(t_stack *a);
void sb(t_stack *a);
void ss(t_stack *a, t_stack *b);

void pa(t_stack *a, t_stack *b);
void pb(t_stack *a, t_stack *b);

void ra(t_stack *a);
void rb(t_stack *b);
void rr(t_stack *a, t_stack *b);
void rra(t_stack *a);
void rrb(t_stack *b);
void rrr(t_stack *a, t_stack *b);

int	assign_values(t_stack *stack, int *arr, int size);
void	fill_array(int *array, char **argv, int size);
int	ft_atoi(const char *str);
void sort_3(t_stack *a);
void sort_4(t_stack *a, t_stack *b);
void sort_5(t_stack *a, t_stack *b);
void push_swap(t_stack *stack_a, t_stack *stack_b, int size);

int	is_array_sorted(t_stack stack);
void	error_and_exit(void);

#endif
