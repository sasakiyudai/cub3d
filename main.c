/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:29:36 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 15:26:51 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	calc(t_info *info)
{
	calc_a(info);
	calc_b(info);
}

int		main_loop(t_info *info)
{
	calc(info);
	if (info->flag.save_flag == 1)
		make_bmp(info);
	draw(info);
	key_update(info);
	return (0);
}

void	init_all(t_info *info)
{
	int i;

	info->sprite = NULL;
	info->index = 0;
	info->flag.numsprite = 0;
	info->tex_index = 0;
	info->flag.player_flag = 0;
	info->key_ar_l = 0;
	info->key_w = 0;
	info->key_s = 0;
	info->key_a = 0;
	info->key_d = 0;
	info->key_ar_r = 0;
	info->key_esc = 0;
	info->buf = NULL;
	info->zbuffer = NULL;
	info->spritedistance = NULL;
	info->spriteorder = NULL;
	info->movespeed = 0.05;
	info->rotspeed = 0.05;
	i = 0;
	while (i < 9)
		info->cub_flags[i++] = 0;
}

int		main(int argc, char *argv[])
{
	t_info info;

	first_set(&info, argc, argv);
	load_texture(&info);
	if (info.flag.save_flag == 0)
		info.win = mlx_new_window(info.mlx, info.width, info.height, "mlx");
	info.img.img = mlx_new_image(info.mlx, info.width, info.height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, \
	&info.img.size_l, &info.img.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	if (info.flag.save_flag == 0)
	{
		mlx_hook(info.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &info);
		mlx_hook(info.win, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, &info);
		mlx_hook(info.win, X_EVENT_KEY_EXIT, 1L << 17, &free_close, &info);
	}
	mlx_loop(info.mlx);
}
