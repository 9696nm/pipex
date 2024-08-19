/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:49:03 by hana              #+#    #+#             */
/*   Updated: 2024/08/19 20:03:05 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headder/pipex.h"

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
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	return (NULL);
}

int	execcmd(char **envp, char *cmd)
{
	char	*path;
	char	**exargv;

	exargv = ft_split(cmd, ' ');
	if (exargv == NULL)
		return (-1);
	path = pathsearch(envp, exargv[0]);
	if (path)
	{
		execve(path, exargv, NULL);
		free(path);
	}
	freedoble(&exargv);
	return (0);
}

int	main(int argc, char *argv[], char **environ)
{
	char	**envp;

	envp = setenvp(environ);
	if (envp == NULL)
		return (perror("envp\n"), 0);
	if (3 < argc)
		read_check(++argv, envp);
	freedoble(&envp);
	return (0);
}

//$ ps f -fA