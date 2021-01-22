/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 23:17:56 by syudai            #+#    #+#             */
/*   Updated: 2020/12/18 23:20:25 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	error(int num, t_info *info)
{
	write(2, "Error\n", 6);
	if (num == 1)
		write(2, "Wrong number of arguments\n", 26);
	else if (num == 2)
		write(2, "Second argument must be --save\n", 31);
	else if (num == 3)
		write(2, "Couldn't read the file\n", 23);
	else if (num == 4)
		write(2, "Invalid cub file\n", 17);
	else if (num == 5)
		write(2, "Map must be within 100*100\n", 27);
	else if (num == 6)
		write(2, "Couldn't malloc\n", 16);
	else if (num == 7)
		only_for_seven(info);
	exit(1);
}

void	draw(t_info *info)
{
	int y;
	int x;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			info->img.data[(info->img.size_l / 4) * y + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}
