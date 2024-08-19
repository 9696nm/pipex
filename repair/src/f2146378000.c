/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:49:03 by hana              #+#    #+#             */
/*   Updated: 2024/08/17 12:43:35 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headder/pipex.h"
#include <stdio.h>

extern char	**environ;

static char	**setenvp(void)
{
	int	i;

	i = 0;
	while (environ[i] && !ft_strnstr(environ[i], "PATH=", 5))
		i++;
	if (environ[i])
		return (ft_split(environ[i], ':'));
	return (NULL);
}

static char	*pathsearch(char **envp, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		path = acrossjoin(envp[i++], cmd, "/");
		if (path == NULL || access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

static void	execcmd(char **envp, char *cmd)
{
	char	*path;
	char	**exargv;

	exargv = ft_split(cmd, ' ');
	path = pathsearch(envp, exargv[0]);
	if (path)
	{
		execve(path, exargv, NULL);
		free(path);
	}
	freedoble(&exargv);
}

static int	pipeout(char **argv, char **envp, int infd)
{
	int		outfd;
	int		pipefd[2];
	pid_t	pid;

	pid = fork();
	if (pipe(pipefd) == -1)
		return (perror("pipe\n"), 0);
	outfd = dup(STDOUT_FILENO);
	if (pid == 0)
	{
		close(pipefd[READ]);
		write(pipefd[WRITE], "out", 3);
		if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		// execcmd(envp, *argv);
		close(pipefd[WRITE]);
	}
	else
	{
		close(pipefd[WRITE]);
		// if (dup2(infd, STDIN_FILENO) == -1)
		// 	return (-1);
		// wait(NULL);
		char buf[4];
		read(pipefd[READ], buf, 3);
		printf("%s\n", buf);
		if (dup2(pipefd[READ], STDIN_FILENO) == -1)
			return (-1);
		// if (dup2(outfd, STDOUT_FILENO) == -1)
		// 	return (-1);
		close(pipefd[READ]);
	}
	return (0);
}

static int	fileout(char **argv, char **envp, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (-1);
		execcmd(envp, *argv);
	}
	return (0);	
}

static int	output_check(char **argv, char **envp)
{
	int	fd;
	int	infd;

	infd = dup(STDIN_FILENO);
	fd = open((argv++)[0], O_RDONLY);
	// if (dup2(fd, STDIN_FILENO) == -1)
	// 	return (-1);
	while (2 < arraylen(argv))
		pipeout(argv++, envp, infd);
	fileout(argv++, envp, open(argv[1], O_WRONLY | O_CREAT | O_TRUNC , 0664));
	return (0);
}

int	main(int argc, char *argv[])
{
	char	**envp;

	envp = setenvp();
	if (envp == NULL)
		return (perror("envp\n"), 0);
	if (2 < argc)
		output_check(++argv, envp);
	freedoble(&envp);
	return (0);
}

//$ ps f -fA