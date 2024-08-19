/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:49:03 by hana              #+#    #+#             */
/*   Updated: 2024/08/19 16:34:34 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headder/pipex.h"
#include <stdio.h>

static char	**setenvp(char **environ)
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

int	execcmd(char **envp, char *cmd)
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

int	main(int argc, char *argv[], char **environ)
{
	int		fl_heardoc;
	char	**envp;

	envp = setenvp(environ);
	if (envp == NULL)
		return (perror("envp\n"), 0);
	if (2 < argc)
		read_check(++argv, envp);
	freedoble(&envp);
	return (0);
}

//$ ps f -fA