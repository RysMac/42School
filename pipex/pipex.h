#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void ft_putchar(char c);
void ft_write(const char *str);
size_t ft_strlen(const char *str);
int ft_strcomp(const char *str1, const char *str2, size_t n);
static char *ft_dir(char *str, char *cmd, int start, size_t l);
static char *ft_getpath(char *str, char *cmd);
void	free_ptr(char **arr);
char *ft_finalpath(char **envp, char **cmds);
int	open_file(char *argv, int i, int *status);

#endif
