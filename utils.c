/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 13:23:22 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 13:23:27 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

size_t	ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

size_t	ft_strchr(char *s, char c)
{
	size_t i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			return (i);
		i++;
		s++;
	}
	return (i);
}

void	ft_strcpy(char *s1, char *s2, size_t n)
{
	while (n--)
		s1[n] = s2[n];
}

char	*ft_strdup(char *s)
{
	size_t	n;
	char	*p;

	n = ft_strlen(s);
	if (!(p = malloc(n + 1)))
		return (NULL);
	p[n] = 0;
	ft_strcpy(p, s, n);
	return (p);
}

char	*ft_strjoin(char *s1, char *s2, ssize_t n1, ssize_t n2)
{
	char *p;

	if (n1 == -1)
		n1 = ft_strlen(s1);
	if (!(p = malloc(n1 + n2 + 1)))
		return (NULL);
	ft_strcpy(p, s1, n1);
	ft_strcpy(p + n1, s2, n2);
	p[n1 + n2] = 0;
	return (p);
}
