/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 01:28:27 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/07/19 01:33:47 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	pid_t	pid;

	pid = fork();
	printf("%6d %6d\n", pid, getpid());
	exit(0);
}