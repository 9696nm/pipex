/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmori <hmori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:14:21 by hmori             #+#    #+#             */
/*   Updated: 2023/10/14 21:25:13 by hmori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *source, int c)
{
	size_t			src_len;
	unsigned char	*src;
	unsigned char	uc;

	src = (unsigned char *)source;
	uc = (unsigned char)c;
	src_len = ft_strlen((char *)src);
	if (src[src_len] == uc)
		return ((char *)(src + src_len));
	while (src_len > 0)
	{
		if (src[src_len - 1] == uc)
			return ((char *)(src + src_len - 1));
		src_len--;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	int		c = 's';
// 	char	test[] = "scsaafb rgr", *p, *q;

// 	p = strrchr(test, c);
// 	q = ft_strrchr(test, c);
// 	printf("source : %s\nsearch : %#x\nord : %s\nft_ : %s\n", test, c, p, q);
// 	return (0);
// }
