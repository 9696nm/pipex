/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmori <hmori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:20:47 by hmori             #+#    #+#             */
/*   Updated: 2023/10/14 20:19:18 by hmori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen((char *)src);
	if (dstsize == 0 || dst == NULL)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	((unsigned char *)dst)[i] = '\0';
	return (src_len);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	size_t	destsize = -1;
// 	char	src[] = {"coucou"};
// 	char	dest[10];

// 	printf("size : %lu\n", destsize);
// 	printf("long : %lu\n", strlcpy(src, dest, destsize));
// 	for (int i = 0; i < sizeof(src); i++)
// 		printf("%#x\n", src[i]);
// 	return (0);
// }
