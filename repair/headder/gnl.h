/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:33:31 by hmori             #+#    #+#             */
/*   Updated: 2024/08/04 13:19:11 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <sys/select.h> //FD_MAX macro

# ifndef FD_MAX
#  define FD_MAX FD_SETSIZE
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# if BUFFER_SIZE > 65536
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 65536
# endif

typedef struct s_mem
{
	ssize_t	read_len;
	char	*result;
	char	pull[BUFFER_SIZE + 1];
}	t_mem;

char	*get_next_line(int fd);

#endif