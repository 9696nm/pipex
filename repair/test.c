/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 01:28:27 by hana/hmori        #+#    #+#             */
/*   Updated: 2024/08/19 15:22:55 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headder/pipex.h"
#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("mitiontest", O_RDONLY);
	printf("%d\n", fd);
	return (0);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*exearg[] = {"grep", "a", "infile", NULL};

// 	fd = open("outfile", O_WRONLY);
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 		perror("dup2\n");
// 	else
// 		execve("/usr/bin/grep", exearg, NULL);
// 	close(fd);
// 	return (0);
// }


// int	main(int argc, char *argv[])
// {
// 	int	fd;

// 	fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return (1);
// 	}

// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		close(fd);
// 		return (1);
// 	}

// 	printf("hello!\n");
// 	close(fd);
// 	return (0);
// }

		// fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR); //normal write
		// fd = open("outfile", O_WRONLY | O_CREAT | O_APPEND , S_IRUSR | S_IWUSR); //append write
		// if (fd == -1)
		// 	return (perror("open"), 0);
		
		// if (dup2(fd, STDOUT_FILENO) == -1)
		// 	exit(0);
		
		// close(fd);
		
		// read(pipefd[READ], buf, 12);
		// printf("f:%s\n", buf);
		
