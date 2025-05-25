#include "pipex.h"

int	open_file(char *argv, int i, int *status)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);

	if (file == -1)
	{
		perror(argv);
		return (-1);
	}
	if (access(argv, F_OK) != 0 || access(argv, R_OK) != 0)
		*status = -1;

	printf("Status : %d\n", *status);
	return (file); // success

	// int	file;

	// file = 0;
	// if (i == 0)
	// 	file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	// else if (i == 1)
	// 	file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// else if (i == 2)
	// 	file = open(argv, O_RDONLY, 0777);
	// if (file == -1)
	// {
	// 	if (errno == EACCES)
	// 	{
	// 		printf("%s: Permission denied\n", argv);
	// 		// exit(1);
	// 	}
	// 	else if (errno == ENOENT)
	// 		printf("%s: No such file or directory\n", argv);
	// 	else
	// 	{
	// 		printf("%s: %s\n", argv, strerror(errno));
	// 		exit(1);
	// 	}
	// }
	// return (file);
}

static char *ft_dir(char *str, char *cmd, int start, size_t l)
{
	char *ptr;
	size_t i;
	size_t cl;
	if (!cmd)
		cl = 0;
	else
		cl = ft_strlen(cmd);
	ptr = (char *)malloc(sizeof(char) * (l + cl + 2));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < l)
	{
		ptr[i] = str[start + i];
		i++;
	}
	ptr[i] = '/';
	i = 0;
	while (i < cl && cmd[i])
	{
		ptr[l + 1 + i] = cmd[i];
		i++;
	}
	ptr[l + cl + 1] = '\0';
	return (ptr);
}

static char *ft_getpath(char *str, char *cmd)
{
	size_t i;
	size_t j;
	char *path;

	i = 0;
	while(str[i] != '=')
		i++;
	while (str[i])
	{
		if (str[i] == '=' || str[i] == ':')
		{
			i++;
			j = 0;
			while (str[i + j] != ':' && str[i + j])
				j++;
			path = ft_dir(str, cmd, i, j);
			if (access(path, X_OK) == 0)
				return (path);
			else
				free(path);
		}
		i++;
	}
	return (NULL);
}

char *ft_finalpath(char **envp, char **cmds)
{
	int i;
	char *path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strcomp(envp[i], "PATH", 4))
		{
			// printf("TRUE IF STATEMENT \n");
			// printf("PATH string: %s\n", envp[i]);
			path = ft_getpath(envp[i], cmds[0]);
			return (path);
		}
		i++;
	}
	return (NULL);
}
