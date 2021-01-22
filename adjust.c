/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:09:56 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 00:26:33 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	calc_a_a(t_info *info, int x)
{
	int texy;
	int color;
	int y;

	y = info->wall.drawstart;
	while (y < info->wall.drawend)
	{
		texy = min((int)info->wall.texpos, info->texheight\
		[info->wall.texnum] - 1);
		info->wall.texpos += info->wall.step;
		color = info->texture[info->wall.texnum][info->texwidth\
		[info->wall.texnum] * texy + info->wall.texx];
		if (info->wall.side == 1)
			color = (color >> 1) & 8355711;
		info->buf[y][x] = color;
		y++;
	}
}

void	adjust_b(t_info *info)
{
	if (info->wall.side == 0)
		info->wall.wallx = info->posy + info->wall.perpwalldist * \
		info->wall.raydiry;
	else
		info->wall.wallx = info->posx + info->wall.perpwalldist * \
		info->wall.raydirx;
	info->wall.wallx -= floor((info->wall.wallx));
	info->wall.texx = (int)(info->wall.wallx * \
	(double)info->texwidth[info->wall.texnum]);
	if (info->wall.side == 0 && info->wall.raydirx > 0)
		info->wall.texx = info->texwidth[info->wall.texnum] - \
		info->wall.texx - 1;
	if (info->wall.side == 1 && info->wall.raydiry < 0)
		info->wall.texx = info->texwidth[info->wall.texnum] - \
		info->wall.texx - 1;
	info->wall.step = 1.0 * info->texheight[info->wall.texnum] / \
	info->wall.lineheight;
	info->wall.texpos = (info->wall.drawstart - info->height / 2 + \
	info->wall.lineheight / 2) * info->wall.step;
}
