/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmori <hmori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:25:21 by hmori             #+#    #+#             */
/*   Updated: 2023/09/27 16:25:21 by hmori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_clause(const char *src, const char *cstr)
{
	size_t	i;

	i = 0;
	if (!*cstr)
		return (0);
	while (cstr[i])
	{
		if (src[i] != cstr[i])
			return (0);
		i++;
	}
	return (1);
}

static int	count_clause(const char *src, const char *cstr)
{
	int	cl;
	int	flag;
	int	cl_cnt;

	flag = 1;
	cl_cnt = 0;
	while (*src)
	{
		cl = check_clause(src, cstr);
		if (cl)
		{
			flag = 1;
			src += ft_strlen((char *)cstr);
		}
		else if (flag)
		{
			flag = 0;
			cl_cnt++;
		}
		else
			src++;
	}
	return (cl_cnt);
}

static void	put_src(char **res, const char *src, int posi, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		res[posi][i] = src[i];
		i++;
	}
	res[posi][i] = '\0';
}

static int	asg_clause(char **res, const char *src, const char *cstr, int posi)
{
	int		cl;
	size_t	size;

	cl = check_clause(src, cstr);
	if (!*src)
		return (0);
	if (cl)
	{
		asg_clause(res, src += ft_strlen((char *)cstr), cstr, posi);
		return (0);
	}
	size = 0;
	while (*src && !check_clause(src, cstr))
	{
		size++;
		src++;
	}
	res[posi] = (char *)malloc(sizeof(char) * (size + 1));
	if (res[posi] == NULL)
		return (1);
	put_src(res, src - size, posi, size);
	asg_clause(res, src, cstr, posi + 1);
	return (0);
}

char	**ft_split(char const *src, char c)
{
	char	cstr[2];
	int		cl_cnt;
	char	**res;

	cstr[0] = c;
	cstr[1] = '\0';
	if (src == NULL)
		return (NULL);
	cl_cnt = count_clause(src, cstr);
	res = (char **)malloc(sizeof(char *) * (cl_cnt + 1));
	if (res == NULL)
		return (NULL);
	res[cl_cnt] = NULL;
	if (!asg_clause(res, src, cstr, 0))
		return (res);
	while (res)
		free(*res++);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	**expected = (char*[6]){"hello,world,42,tokyo", NULL};
// 	char	*src = "hello,world,42,tokyo";
// 	// char	*cstr = "012";
// 	char	cstr = ' ';
// 	char	**res;

// 	res = ft_split(src, cstr);
// 	if (res)
// 	{
// 		for (int i = 0; res[i]; i++)
// 			printf("%s$\n", res[i]);
// 		for (int i = 0; res[i]; i++)
// 			printf("%s$\n", expected[i]);
// 		free (res);
// 	}
// 	else
// 		printf("Memory allocation error.\n");
// 	return (0);
// }
