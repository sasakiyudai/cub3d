/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:33:09 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 00:21:09 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	init_wall(t_info *info, int x)
{
	info->wall.camerax = 2 * x / (double)info->width - 1;
	info->wall.raydirx = info->dirx + info->planex * info->wall.camerax;
	info->wall.raydiry = info->diry + info->planey * info->wall.camerax;
	info->wall.mapx = (int)info->posx;
	info->wall.mapy = (int)info->posy;
	info->wall.deltadistx = fabs(1 / info->wall.raydirx);
	info->wall.deltadisty = fabs(1 / info->wall.raydiry);
	info->wall.hit = 0;
}

void	calc_dist(t_info *info)
{
	if (info->wall.raydirx < 0)
	{
		info->wall.stepx = -1;
		info->wall.sidedistx = (info->posx - info->wall.mapx) * \
		info->wall.deltadistx;
	}
	else
	{
		info->wall.stepx = 1;
		info->wall.sidedistx = (info->wall.mapx + 1.0 - info->posx) * \
		info->wall.deltadistx;
	}
	if (info->wall.raydiry < 0)
	{
		info->wall.stepy = -1;
		info->wall.sidedisty = (info->posy - info->wall.mapy) * \
		info->wall.deltadisty;
	}
	else
	{
		info->wall.stepy = 1;
		info->wall.sidedisty = (info->wall.mapy + 1.0 - info->posy) * \
		info->wall.deltadisty;
	}
}

void	do_dda(t_info *info)
{
	while (info->wall.hit == 0)
	{
		if (info->wall.sidedistx < info->wall.sidedisty)
		{
			info->wall.sidedistx += info->wall.deltadistx;
			info->wall.mapx += info->wall.stepx;
			info->wall.side = 0;
		}
		else
		{
			info->wall.sidedisty += info->wall.deltadisty;
			info->wall.mapy += info->wall.stepy;
			info->wall.side = 1;
		}
		if (info->map.world[info->wall.mapx][info->wall.mapy] == 1)
			info->wall.hit = 1;
	}
}

void	adjust(t_info *info)
{
	if (info->wall.side == 0)
		info->wall.perpwalldist = (info->wall.mapx - info->posx + (1 - \
		info->wall.stepx) / 2) / info->wall.raydirx;
	else
		info->wall.perpwalldist = (info->wall.mapy - info->posy + (1 - \
		info->wall.stepy) / 2) / info->wall.raydiry;
	info->wall.lineheight = (int)(info->height / info->wall.perpwalldist);
	info->wall.drawstart = -info->wall.lineheight / 2 + info->height / 2;
	if (info->wall.drawstart < 0)
		info->wall.drawstart = 0;
	info->wall.drawend = info->wall.lineheight / 2 + info->height / 2;
	if (info->wall.drawend >= info->height)
		info->wall.drawend = info->height - 1;
	if (info->wall.side == 1 && info->wall.raydiry < 0)
		info->wall.texnum = 2;
	else if (info->wall.side == 1)
		info->wall.texnum = 3;
	else if (info->wall.side == 0 && info->wall.raydirx < 0)
		info->wall.texnum = 0;
	else
		info->wall.texnum = 1;
	adjust_b(info);
}

void	calc_a(t_info *info)
{
	int y;
	int x;

	x = 0;
	while (x < info->width)
	{
		init_wall(info, x);
		calc_dist(info);
		do_dda(info);
		adjust(info);
		y = 0;
		while (y < info->wall.drawstart)
			info->buf[y++][x] = info->ceiling;
		calc_a_a(info, x);
		y = info->wall.drawend;
		while (y < info->height)
			info->buf[y++][x] = info->floor;
		info->zbuffer[x] = info->wall.perpwalldist;
		x++;
	}
}
