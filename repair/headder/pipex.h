/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:20:27 by hmori             #+#    #+#             */
/*   Updated: 2024/08/17 15:26:27 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> //system call
# include <stdlib.h> //malloc
# include <stdarg.h> //va_arg
# include <sys/wait.h> //waitpidq

# include <stdint.h> //int value macro
# include <stddef.h> //type size_t
# include <fcntl.h> //acsess parameter macro
# include <sys/stat.h> //open parameter macro

# include <errno.h> //error parameter

# include "gnl.h"
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# if BUFFER_SIZE > 65536
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 65536
# endif

typedef enum t_pipe
{
    READ = 0,
    WRITE = 1
} e_pipe;

char	*acrossjoin(char *front, char *bottom, char *ch);

int 	arraylen(char **array);
void	freedoble(char ***array);
char	*read_heredoc(int fd, char *endcmd);

#endif
