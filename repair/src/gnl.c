/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:58:22 by hmori             #+#    #+#             */
/*   Updated: 2024/07/25 22:09:19 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headder/gnl.h"

static char	*na_strchr(const char *source, int c)
{
	while (*source)
	{
		if (*source == (unsigned char)c)
			return ((char *)source);
		source++;
	}
	return ((char *)source);
}

static char	*rescopy(t_mem lst, char **oldres)
{
	char	*joint;

	joint = na_strchr(lst.pull, '\n');
	if (*joint)
		lst.pull[joint - lst.pull + 1] = '\0';
	joint = ft_strjoin(*oldres, lst.pull);
	free(*oldres);
	return (joint);
}

char	*get_next_line(int fd)
{
	t_mem		lst;
	static char	memry[FD_MAX][BUFFER_SIZE + 1];

	lst.result = malloc(sizeof(char));
	*lst.result = '\0';
	lst.read_len = BUFFER_SIZE;
	while (lst.read_len && 0 <= fd && fd < FD_MAX)
	{
		ft_bzero(lst.pull, BUFFER_SIZE + 1);
		if (*memry[fd] == '\0')
			lst.read_len = read(fd, lst.pull, BUFFER_SIZE);
		else
			ft_strlcpy(lst.pull, memry[fd] + 1, ft_strlen(memry[fd]) + 1);
		if (lst.read_len < 0 || lst.result == NULL)
			break ;
		ft_strlcpy(memry[fd], na_strchr(lst.pull, '\n'), lst.read_len + 1);
		lst.result = rescopy(lst, &(lst.result));
		if (*memry[fd] == '\n' || (*lst.result && lst.read_len == 0))
			return (lst.result);
	}
	if (lst.result)
		free(lst.result);
	return (NULL);
}
