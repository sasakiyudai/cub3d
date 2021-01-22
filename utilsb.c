/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 13:23:51 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 13:24:12 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

int		min(int a, int b)
{
	return (a > b ? b : a);
}

void	isvalid(char c, t_info *info)
{
	if (c != '0' && c != '1' && c != '2' && c != 'N'
		&& c != 'S' && c != 'W' && c != 'E' && c != ' ')
		error(4, info);
}

int		ft_ischarset(char c, char *charset)
{
	unsigned int i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_check(int sign, long rev, int i, const char *str)
{
	if (rev > (__LONG_MAX__ / 10))
		return (0);
	if (rev == (__LONG_MAX__ / 10))
	{
		if (sign == 1)
		{
			if (str[i] > '7')
				return (0);
		}
		else
		{
			if (str[i] > '8')
				return (0);
		}
	}
	return (1);
}

int		ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	rev;

	i = 0;
	sign = 1;
	rev = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (ft_check(sign, rev, i, str))
			rev = rev * 10 + (str[i] - '0');
		else
			return (sign == 1 ? -1 : 0);
		i++;
	}
	if (rev > __INT_MAX__)
		return (-1);
	return (sign * rev);
}
