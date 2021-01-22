/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 13:16:44 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 13:36:12 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	key_update_c(t_info *info)
{
	double olddirx;
	double oldplanex;

	if (info->key_ar_l)
	{
		olddirx = info->dirx;
		info->dirx = info->dirx * cos(info->rotspeed) - \
		info->diry * sin(info->rotspeed);
		info->diry = olddirx * sin(info->rotspeed) + \
		info->diry * cos(info->rotspeed);
		oldplanex = info->planex;
		info->planex = info->planex * cos(info->rotspeed) - \
		info->planey * sin(info->rotspeed);
		info->planey = oldplanex * sin(info->rotspeed) + \
		info->planey * cos(info->rotspeed);
	}
	if (info->key_esc)
		free_close(info);
}

void	key_update_f(t_info *info)
{
	if (info->key_a)
	{
		if (!info->map.world[(int)(info->posx - info->planex * \
		info->movespeed)][(int)(info->posy)])
			info->posx -= info->planex * info->movespeed;
		if (!info->map.world[(int)(info->posx)][(int)(info->posy - \
		info->planey * info->movespeed)])
			info->posy -= info->planey * info->movespeed;
	}
}

void	key_update_b(t_info *info)
{
	double olddirx;
	double oldplanex;

	key_update_f(info);
	if (info->key_ar_r)
	{
		olddirx = info->dirx;
		info->dirx = info->dirx * cos(-info->rotspeed) - info->diry * \
		sin(-info->rotspeed);
		info->diry = olddirx * sin(-info->rotspeed) + info->diry * \
		cos(-info->rotspeed);
		oldplanex = info->planex;
		info->planex = info->planex * cos(-info->rotspeed) - info->planey * \
		sin(-info->rotspeed);
		info->planey = oldplanex * sin(-info->rotspeed) + info->planey * \
		cos(-info->rotspeed);
	}
	key_update_c(info);
}

void	key_update_neo(t_info *info)
{
	if (info->key_d)
	{
		if (!info->map.world[(int)(info->posx + info->planex * \
		info->movespeed)][(int)(info->posy)])
			info->posx += info->planex * info->movespeed;
		if (!info->map.world[(int)(info->posx)][(int)(info->posy + \
		info->planey * info->movespeed)])
			info->posy += info->planey * info->movespeed;
	}
}

void	key_update(t_info *info)
{
	if (info->key_w)
	{
		if (!info->map.world[(int)(info->posx + info->dirx * \
		info->movespeed)][(int)(info->posy)])
			info->posx += info->dirx * info->movespeed;
		if (!info->map.world[(int)(info->posx)][(int)(info->posy + \
		info->diry * info->movespeed)])
			info->posy += info->diry * info->movespeed;
	}
	if (info->key_s)
	{
		if (!info->map.world[(int)(info->posx - info->dirx * \
		info->movespeed)][(int)(info->posy)])
			info->posx -= info->dirx * info->movespeed;
		if (!info->map.world[(int)(info->posx)][(int)(info->posy - \
		info->diry * info->movespeed)])
			info->posy -= info->diry * info->movespeed;
	}
	key_update_neo(info);
	key_update_b(info);
}
