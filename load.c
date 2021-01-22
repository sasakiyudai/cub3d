/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 00:40:28 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 01:03:58 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	fill_map(int x, int y, t_info *info)
{
	if (info->map.checkie[x][y] == 1 || info->map.checkie[x][y] == 8)
		return ;
	if (info->map.checkie[x][y] == 9)
	{
		info->map.checkie[x][y] = 8;
		return ;
	}
	if (info->map.checkie[x][y] == 0 || info->map.checkie[x][y] == 2)
	{
		info->map.checkie[x][y] = 8;
		fill_map(x, y - 1, info);
		fill_map(x + 1, y, info);
		fill_map(x, y + 1, info);
		fill_map(x - 1, y, info);
	}
}

void	check_map(t_info *info)
{
	int i;

	i = 0;
	while (i < 102)
	{
		if (info->map.checkie[0][1] != 9)
			error(4, info);
		if (info->map.checkie[i][0] != 9)
			error(4, info);
		if (info->map.checkie[101][i] != 9)
			error(4, info);
		if (info->map.checkie[i][101] != 9)
			error(4, info);
		i++;
	}
}

void	set_sprites(t_info *info)
{
	int count;
	int i;
	int j;

	i = 0;
	count = 0;
	if (!(info->sprite = (t_sprite *)malloc(sizeof(t_sprite) * \
	info->flag.numsprite)))
		error(6, info);
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			if (info->map.world[i][j] == 2)
			{
				info->sprite[count].x = i + 0.5;
				info->sprite[count].y = j + 0.5;
				info->sprite[count].texture = 4;
				count++;
			}
			j++;
		}
		i++;
	}
}

void	load_image(t_info *info, char *path, t_img *img)
{
	int x;
	int y;

	get_image(info, path, img);
	x = 0;
	while (x < (img->img_width * img->img_height))
		info->texture[info->tex_index][x++] = 0;
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, \
	&img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			info->texture[info->tex_index][img->img_width * y + x] = \
			img->data[(img->size_l / 4) * y + x];
			x++;
		}
		y++;
	}
	info->tex_index++;
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img img;

	load_image(info, info->path.north, &img);
	load_image(info, info->path.south, &img);
	load_image(info, info->path.west, &img);
	load_image(info, info->path.east, &img);
	load_image(info, info->path.splite, &img);
	free(info->path.north);
	free(info->path.south);
	free(info->path.west);
	free(info->path.east);
	free(info->path.splite);
}
