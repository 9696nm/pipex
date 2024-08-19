/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_units.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:33:47 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/08/19 16:35:14 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headder/pipex.h"

static int	pipeout(char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (perror("pipe\n"), 0);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[READ]);
		if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		execcmd(envp, *argv);
		close(pipefd[WRITE]);
	}
	else
	{
		close(pipefd[WRITE]);
		if (dup2(pipefd[READ], STDIN_FILENO) == -1)
			return (-1);
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

static int	read_check(char **argv, char **envp)
{
	int	fd;

	fd = open((argv++)[0], O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	while (2 < arraylen(argv))
		pipeout(argv++, envp);
	fileout(argv++, envp, open(argv[1], O_WRONLY | O_CREAT | O_TRUNC , 0664));
	return (0);
}
