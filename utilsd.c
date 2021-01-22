/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 13:32:42 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 21:43:25 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	get_image(t_info *info, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, \
	&img->img_width, &img->img_height);
	if (img->img == 0)
		error(7, info);
	info->texwidth[info->tex_index] = img->img_width;
	info->texheight[info->tex_index] = img->img_height;
	if (!(info->texture[info->tex_index] = (int *)malloc(sizeof(int) * \
	(img->img_width * img->img_height))))
		error(6, info);
}

void	mallocate(t_info *info)
{
	int i;

	if (!(info->buf = (int **)malloc(sizeof(int *) * info->height)))
		error(6, info);
	i = 0;
	while (i < info->height)
	{
		if (!(info->buf[i] = (int *)malloc(sizeof(int) * info->width)))
			error(6, info);
		i++;
	}
	if (!(info->zbuffer = malloc(sizeof(double) * info->width)))
		error(6, info);
	if (!(info->spriteorder = malloc(sizeof(int) * info->flag.numsprite)))
		error(6, info);
	if (!(info->spritedistance = malloc(sizeof(double) * \
	info->flag.numsprite)))
		error(6, info);
}

void	first_set(t_info *info, int argc, char *argv[])
{
	int i;

	info->mlx = mlx_init();
	info->flag.save_flag = 0;
	if (argc <= 1 || 4 <= argc)
		error(1, info);
	if (argc == 3 && ft_memcmp(argv[2], "--save", 7))
		error(2, info);
	if (argc == 3 && !ft_memcmp(argv[2], "--save", 7))
		info->flag.save_flag = 1;
	init_all(info);
	check_file_name(argv[1], info);
	read_cub(argv[1], info);
	i = 0;
	while (i < 9)
		if (info->cub_flags[i++] != 1)
			error(4, info);
	mallocate(info);
}
