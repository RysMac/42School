#ifndef LIBFT_H
#define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	void	*content;
	struct s_list	*next;
}	t_list;

// Part 2
void	ft_putchar_fd(char *c, int fd);
void	ft_putstr_fd(char *s, int fd);

// bonus functions
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int	ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// to be deleted
void	ft_changechar(char *str);
void	ft_changepointer(char **oldstring);

#endif
