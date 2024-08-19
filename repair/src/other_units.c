/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_units.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:13:42 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/08/19 22:35:37 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headder/pipex.h"

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

int	arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	freedoble(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i])
		free((*array)[i++]);
	free(*array);
}
