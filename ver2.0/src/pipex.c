/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 05:22:36 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/12/11 15:27:16 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	input_set(char *argv, int bitbask)
{
	int	fd;

	fd = open(argv, bitbask);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		perror(argv);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

static int	pipeout(char *argv)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[READ]);
		if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
			errorexit("dup2");
		execset(argv);
	}
	close(pipefd[WRITE]);
	dup2(pipefd[READ], STDIN_FILENO);
	close(pipefd[READ]);
	return (0);
}

static int	fileout(char **argv, int bitmask)
{
	int		fd;
	pid_t	pid;

	fd = open(argv[1], bitmask, 0664);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		errorexit(argv[1]);
	}
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			errorexit("dup2");
		execset(argv[0]);
	}
	close(fd);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc < 3)
		return (0);
	argv++;
	input_set(argv++[0], O_RDONLY);
	pipeout(*argv++);
	fileout(argv, O_WRONLY | O_CREAT | O_TRUNC);
	return (0);
}
