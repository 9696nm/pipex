/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_units.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 05:22:36 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/08/22 16:49:18 by hana/hmori       ###   ########.fr       */
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

static int	heredoc_set(char **argv)
{
	char	*heredoc;
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[READ]);
		heredoc = read_heredoc(STDIN_FILENO, argv[1]);
		if (heredoc == NULL)
			exit(EXIT_FAILURE);
		write(pipefd[WRITE], heredoc, ft_strlen(heredoc));
		free(heredoc);
		close(pipefd[WRITE]);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
	close(pipefd[WRITE]);
	dup2(pipefd[READ], STDIN_FILENO);
	close(pipefd[READ]);
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
	unsigned int	flag_hd;

	if (argc < 3)
		return (0);
	flag_hd = 0b0;
	argv++;
	if (ft_strncmp(argv[0], "here_doc", ft_strlen(argv[0])) == 0)
	{
		flag_hd = 1 << ENABLE_HERE_DOC;
		if (heredoc_set(argv++) == -1)
			return (-1);
	}
	else
		input_set(argv++[0], O_RDONLY);
	while (4 < argc--)
		pipeout(*argv++);
	if (flag_hd & (1 << ENABLE_HERE_DOC))
		fileout(argv, O_WRONLY | O_CREAT | O_APPEND);
	else
		fileout(argv, O_WRONLY | O_CREAT | O_TRUNC);
	return (0);
}
