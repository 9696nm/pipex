/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_units.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 05:22:36 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/08/19 15:52:12 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headder/pipex.h"

static int	input_set(char **argv)
{
	int	fd;
	
	fd = open((argv++)[0], O_RDONLY);
	if (fd == -1)
	{
		perror("bash: mitiontest");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
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
			exit(1);
		write(pipefd[WRITE], heredoc, ft_strlen(heredoc));
		free(heredoc);
		close(pipefd[WRITE]);
		exit(0);
	}
	wait(NULL);
	close(pipefd[WRITE]);
	if (dup2(pipefd[READ], STDIN_FILENO) == -1)
		return (-1);
	close(pipefd[READ]);
	return (0);
}

static int	pipeout(char **argv, char **envp)
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
			exit(1);
		if (execcmd(envp, *argv) == -1)
			exit(1);
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

int	read_check(char **argv, char **envp)
{
	unsigned int	flag_hd;

	flag_hd = 0b0;
	if (ft_strncmp(argv[0], "here_doc", ft_strlen(argv[0])) == 0)
	{
		flag_hd = 1 << 0;
		if (heredoc_set(argv) == -1)
			return (-1);
		argv += 2;
	}
	else
		if (input_set(argv++) == -1)
			return (-1);
	while (2 < arraylen(argv))
		pipeout(argv++, envp);
	if (flag_hd & (1 << 0))
		fileout(argv++, envp, open(argv[1], O_WRONLY | O_CREAT | O_TRUNC , 0664));
	else
		fileout(argv++, envp, open(argv[1], O_WRONLY | O_CREAT | O_APPEND , 0664));
	return (0);
}
