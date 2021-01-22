/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 22:32:23 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 15:06:18 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

int		key_release(int key, t_info *info)
{
	if (key == K_ESC)
		free_close(info);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_AR_L)
		info->key_ar_l = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_AR_R)
		info->key_ar_r = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_D)
		info->key_d = 0;
	return (0);
}

int		key_press(int key, t_info *info)
{
	if (key == K_ESC)
		free_close(info);
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_AR_L)
		info->key_ar_l = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_AR_R)
		info->key_ar_r = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_D)
		info->key_d = 1;
	return (0);
}

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}

void	check_file_name(char *name, t_info *info)
{
	int i;

	i = 0;
	while (name[i])
		i++;
	if (ft_memcmp(name + i - 4, ".cub", 5))
	{
		error(4, info);
	}
	if (!ft_memcmp(name + i - 4, ".cub", 5) && name[0] == '.')
	{
		error(4, info);
	}
}
