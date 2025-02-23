/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:20:27 by hmori             #+#    #+#             */
/*   Updated: 2024/08/29 17:46:57 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> //system call
# include <stdio.h> //perror
# include <stdlib.h> //malloc
# include <stdarg.h> //va_arg
# include <sys/wait.h> //waitpid

# include <stdint.h> //int value macro
# include <stddef.h> //type size_t
# include <fcntl.h> //acsess parameter macro
# include <sys/stat.h> //open parameter macro

# include <errno.h> //error parameter

# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# if BUFFER_SIZE > 65536
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 65536
# endif

typedef enum e_pipe
{
	READ = 0,
	WRITE = 1
}	t_pipe;

typedef enum e_flag
{
	ENABLE_HERE_DOC = 0
}	t_flag;

typedef struct s_readline
{
	ssize_t	read_len;
	char	pull[BUFFER_SIZE + 1];
}	t_rline;

extern char	**environ;

void	execset(char *cmd);

int		read_check(char **argv);

char	*read_heredoc(int fd, char *endcmd);

void	errorexit(const char *errstr);

char	*acrossjoin(char *front, char *bottom, char *ch);

void	freedoble(char ***array);
#endif
