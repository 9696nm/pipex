/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:49:03 by hana              #+#    #+#             */
/*   Updated: 2024/08/24 22:26:24 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	errorexit(const char *errstr)
{
	perror(errstr);
	exit(EXIT_FAILURE);
}

static char	*pathsearch(char *cmd)
{
	int		i;
	char	**envp;
	char	*path;

	i = 0;
	while (environ[i] && !ft_strnstr(environ[i], "PATH=", 5))
		i++;
	if (environ[i])
		envp = ft_split(environ[i], ':');
	if (environ[i] == NULL || envp == NULL)
		errorexit(NULL);
	i = 0;
	while (envp[i])
	{
		path = acrossjoin(envp[i++], cmd, "/");
		if (path == NULL)
			errorexit(NULL);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	freedoble(&envp);
	return (path);
}

void	execset(char *cmd)
{
	char	*path;
	char	**exargv;

	exargv = ft_split(cmd, ' ');
	if (exargv == NULL)
		errorexit(NULL);
	path = pathsearch(exargv[0]);
	if (path)
	{
		execve(path, exargv, NULL);
		errorexit(NULL);
	}
	freedoble(&exargv);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	errorexit(cmd);
}

char	*acrossjoin(char *front, char *bottom, char *ch)
{
	int		buffer;
	char	*result;

	buffer = ft_strlen(ch) + ft_strlen(front) + ft_strlen(bottom) + 1;
	result = malloc(sizeof(char) * (buffer));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, front, buffer);
	ft_strlcat(result, ch, buffer);
	ft_strlcat(result, bottom, buffer);
	return (result);
}

void	freedoble(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i])
		free((*array)[i++]);
	free(*array);
}

//$ ps f -fA