/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:10:32 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/08/22 16:49:24 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*rescopy(t_rline set, char **oldres)
{
	char	*joint;

	set.pull[set.read_len] = '\0';
	joint = ft_strjoin(*oldres, set.pull);
	free(*oldres);
	return (joint);
}

static char	*read_line(int fd)
{
	char	*result;
	t_rline	set;

	result = malloc(sizeof(char));
	if (result == NULL)
		return (NULL);
	*result = '\0';
	set.read_len = BUFFER_SIZE;
	write(STDOUT_FILENO, "pipe heredoc> ", 14);
	while (set.read_len && result)
	{
		set.read_len = read(fd, set.pull, BUFFER_SIZE);
		if (set.read_len == -1)
			break ;
		result = rescopy(set, &result);
		if (ft_strchr(set.pull, '\n') && result)
			return (result);
	}
	free(result);
	return (NULL);
}

static char	*concat_list(t_list *lst)
{
	size_t	buffer;
	char	*result;
	t_list	*lstcopy;

	buffer = 1;
	lstcopy = lst;
	while (lstcopy->next)
	{
		buffer += ft_strlen(lstcopy->next->content);
		lstcopy = lstcopy->next;
	}
	result = malloc(sizeof(char) * (buffer));
	if (result == NULL)
		return (NULL);
	*result = '\0';
	while (lst->next)
	{
		ft_strlcat(result, lst->next->content, buffer);
		lst = lst->next;
	}
	return (result);
}

static void	content_clear(void *content)
{
	if (content)
		free(content);
}

char	*read_heredoc(int fd, char *endstr)
{
	char	*pull;
	char	*result;
	t_list	*lst;

	lst = ft_lstnew(NULL);
	if (lst == NULL)
		return (NULL);
	result = NULL;
	while (result == NULL)
	{
		pull = read_line(fd);
		if (pull == NULL)
			break ;
		if (ft_strncmp(pull, endstr, ft_strlen(pull)) == '\n')
		{
			result = concat_list(lst);
			free(pull);
		}
		else
			ft_lstadd_back(&lst, ft_lstnew(pull));
	}
	ft_lstclear(&lst, *content_clear);
	free(lst);
	return (result);
}

// int	main(void)
// {
// 	char	*buf;

// 	buf = read_heredoc(STDIN_FILENO, "EOF");
// 	printf("ret:%s\n", buf);
// 	free(buf);
// 	return (0);
// }
