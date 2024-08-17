/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:10:32 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/08/17 22:17:32 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headder/pipex.h"
#include <stdio.h>

char	*pullcheck()
char	*read_heredoc(int fd, char *endcmd)
{
	ssize_t	read_len;
	char	pull[BUFFER_SIZE + 1];
	char	*result;

	read_len = BUFFER_SIZE;
	result = malloc(sizeof(char));
	*result = '\0';
	while (read_len)
	{
		read_len = read(fd, pull, BUFFER_SIZE);
		ft_strchr(pull, '\n')
		printf("ret:%li\n", read_len);
		printf("%d:%d:%d:%d\n", pull[0], pull[1], pull[2], pull[3]);
	}
	return (NULL);
}

int	main(void)
{
	char	*buf;

	buf = read_heredoc(STDIN_FILENO, "EOF");
	// free(buf);
	return (0);
}

