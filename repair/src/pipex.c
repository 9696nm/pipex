/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:49:03 by hana              #+#    #+#             */
/*   Updated: 2024/07/19 17:59:13 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <stdio.h>

extern char	**environ;

static char **setenvp(void)
{
	int	i;

	i = 0;
	while (environ[i] && !ft_strnstr(environ[i], "PATH=", 5))
		i++;
	if (environ[i])
		return (ft_split(environ[i], ':'));
	return (NULL);
}

static char	*pathjoin(char *dir, char *cmd)
{
	int		buffer;
	char	*path;

	buffer = (ft_strlen(dir) + 1 + ft_strlen(cmd)) + 1;
	path = malloc(sizeof(char) * (buffer));
	if (path == NULL)
		return (NULL);
	ft_strlcpy(path, dir, buffer);
	ft_strlcat(path, "/", buffer);
	ft_strlcat(path, cmd, buffer);
	return (path);
}

static char	*accesscheck(char **envp, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		path = pathjoin(envp[i++], cmd);
		if (path == NULL || access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

static void	execcmd(char *path)
{
	char	*exargv[] = {"cat", "infile", NULL};
	// char	*exargv[] = {"ls", "-a", NULL};
	
	if (path == NULL)
		return ;
	execve(path, exargv, NULL);
	free(path);
}

int	main(int argc, char *argv[])
{
	int		i;
	char	**envp;
	pid_t	pid;

	envp = setenvp();
	if (envp == NULL)
		return (printf("PATH is not found\n"), 0);
	pid = fork();
	if (pid == 0)
		execcmd(accesscheck(envp, "cat"));
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (0);
}

//$ ps f -fA