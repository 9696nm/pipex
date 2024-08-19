/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_units.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:13:42 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/08/13 21:26:29 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headder/pipex.h"

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
