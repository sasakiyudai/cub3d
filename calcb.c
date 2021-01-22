/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 22:24:27 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 00:23:23 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	support_support(t_info *info)
{
	if (info->splite.drawstarty < 0)
		info->splite.drawstarty = 0;
	info->splite.drawendy = info->splite.spriteheight / 2 + info->height / 2;
	if (info->splite.drawendy >= info->height)
		info->splite.drawendy = info->height - 1;
	info->splite.spritewidth = (int)fabs((info->height / \
	info->splite.transformy));
	info->splite.drawstartx = -info->splite.spritewidth / 2 + \
	info->splite.spritescreenx;
	if (info->splite.drawstartx < 0)
		info->splite.drawstartx = 0;
	info->splite.drawendx = info->splite.spritewidth / 2 + \
	info->splite.spritescreenx;
	if (info->splite.drawendx >= info->width)
		info->splite.drawendx = info->width - 1;
}

void	support(t_info *info, int i)
{
	info->splite.spritex = info->sprite[info->spriteorder[i]].x - info->posx;
	info->splite.spritey = info->sprite[info->spriteorder[i]].y - info->posy;
	info->splite.invdet = 1.0 / (info->planex * info->diry - info->dirx * \
	info->planey);
	info->splite.transformx = info->splite.invdet * (info->diry * \
	info->splite.spritex - info->dirx * info->splite.spritey);
	info->splite.transformy = info->splite.invdet * (-info->planey * \
	info->splite.spritex + info->planex * info->splite.spritey);
	info->splite.spritescreenx = (int)((info->width / 2) * \
	(1 + info->splite.transformx / info->splite.transformy));
	info->splite.spriteheight = (int)fabs((info->height / \
	info->splite.transformy));
	info->splite.drawstarty = -info->splite.spriteheight / 2 + \
	info->height / 2;
	support_support(info);
}

void	second_support_support(t_info *info, int stripe, int texx, int i)
{
	int y;
	int d;
	int texy;
	int color;

	y = info->splite.drawstarty;
	while (y < info->splite.drawendy)
	{
		d = y * 256 - info->height * 128 + info->splite.spriteheight * 128;
		texy = ((d * info->texheight[4]) / info->splite.spriteheight) / 256;
		color = info->texture[info->sprite[info->spriteorder[i]].texture]\
		[info->texwidth[4] * texy + texx];
		if ((color & 0x00FFFFFF) != 0)
			info->buf[y][stripe] = color;
		y++;
	}
}

void	second_support(t_info *info, int i)
{
	int stripe;
	int texx;

	stripe = info->splite.drawstartx;
	while (stripe < info->splite.drawendx)
	{
		texx = (int)((256 * (stripe - (-info->splite.spritewidth / 2 + \
		info->splite.spritescreenx)) * info->texwidth[4] / \
		info->splite.spritewidth) / 256);
		if (info->splite.transformy > 0 && stripe > 0 && stripe < \
		info->width && info->splite.transformy < info->zbuffer[stripe])
			second_support_support(info, stripe, texx, i);
		stripe++;
	}
}

void	calc_b(t_info *info)
{
	int i;

	i = 0;
	while (i < info->flag.numsprite)
	{
		info->spriteorder[i] = i;
		info->spritedistance[i] = ((info->posx - info->sprite[i].x) * \
		(info->posx - info->sprite[i].x) + (info->posy - info->sprite[i].y) * \
		(info->posy - info->sprite[i].y));
		i++;
	}
	sortsprites(info->spriteorder, info->spritedistance, info);
	i = 0;
	while (i < info->flag.numsprite)
	{
		support(info, i);
		second_support(info, i);
		i++;
	}
}
