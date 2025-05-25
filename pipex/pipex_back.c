#include "pipex.h"
#include "libft/libft.h"

void ft_perror(char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

int ft_fork(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: problem with creating child process. Fork failed. \n");
		exit(1);
	}
	return (pid);
}

void ft_execve(char *path, char **cmds, char **envp)
{
	if (!cmds || !cmds[0])
	{
		ft_perror("Fail");
		fprintf(stderr, "pipex: empty command\n");
		free(path);
		free_ptr(cmds);
		exit(127);  // exit code 127 = command not found
	}

	if (!path)
	{
		ft_putstr_fd(cmds[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_ptr(cmds);
		exit(127);
	}

	if (execve(path, cmds, envp) == -1)
		{
			free(path);
			free_ptr(cmds);
			// perror(*cmds);
			exit(1);
		}
}

int child_process(char *path, char **cmds, char **envp)
{
	int pid;
	int fd[2];

	if (pipe(fd) == -1) { return 1; }
	pid = ft_fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_execve(path, cmds, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		free(path);
		free_ptr(cmds);
		return (pid);
	}
}

void execute(int argc, char *argv[], char **envp, int file_out)
{
	int i;
	char **cmds;
	int pid;
	char *path;

	i = 2;
	while (i < argc - 1)
	{
		cmds = ft_split(argv[i] ,' ');
		path = ft_finalpath(envp, cmds);
		if (argc - i - 1 < 2)
		{
			pid = ft_fork();
			if (pid == 0)
			{
				dup2(file_out, STDOUT_FILENO);
				ft_execve(path, cmds, envp);
			}
			else
			{
				waitpid(pid, NULL, 0);
			}
			free(path);
			free_ptr(cmds);
			break;
		}
		pid = child_process(path, cmds, envp);
		// free_ptr(cmds);
		// 	free(path);
		i++;
	}
}

int main(int argc, char *argv[], char **envp)
{
	int i;
	int fd_in;
	int	fd_out;
	int n_cmds;

	if (argc < 5)
	{
		write(2, "Error: Too few input arguments.\n", 32);
		return (1);
	}
	// int saved_stdout = dup(STDOUT_FILENO);

	// Print the number of arguments
	// printf("Number of arguments: %d\n", argc);

	// Print all arguments
	// for (int i = 0; i < argc; i++)
	// {
	// 	printf("Argument %d: %s\n", i, argv[i]);
	// }

	fd_in = open_file(argv[1], 2);
	fd_out = open_file(argv[argc - 1], 1);
	n_cmds = argc - 3;

	dup2(fd_in, STDIN_FILENO);
	execute(argc, argv, envp, fd_out);
	// dup2(saved_stdout, STDOUT_FILENO);
	// close(saved_stdout);
	close(fd_in);
	close(fd_out);

	return (0);
}
