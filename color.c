/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 22:34:49 by syudai            #+#    #+#             */
/*   Updated: 2020/12/18 23:16:42 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

unsigned char g_bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0,
	0, 0, 0, 54, 0, 0, 0};
unsigned char g_bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 24, 0};
unsigned char g_bmppad[3] = {0, 0, 0};

int		get_rgb(int trgb, int i)
{
	if (i == 0)
		return ((trgb & (0xFF << 16)) / (256 * 256));
	else if (i == 1)
		return ((trgb & (0xFF << 8)) / 256);
	else
		return (trgb & 0xFF);
}

void	loop_set(t_info *info, unsigned char *img)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (i < info->width)
	{
		j = 0;
		while (j < info->height)
		{
			x = i;
			y = (info->height - 1) - j;
			img[(y * info->width + x) * 3 + 2] = get_rgb(info->buf[y][x], 0);
			img[(y * info->width + x) * 3 + 1] = get_rgb(info->buf[y][x], 1);
			img[(y * info->width + x) * 3 + 0] = get_rgb(info->buf[y][x], 2);
			j++;
		}
		i++;
	}
}

void	set_header(int filesize, t_info *info)
{
	g_bmpfileheader[2] = (unsigned char)(filesize);
	g_bmpfileheader[3] = (unsigned char)(filesize >> 8);
	g_bmpfileheader[4] = (unsigned char)(filesize >> 16);
	g_bmpfileheader[5] = (unsigned char)(filesize >> 24);
	g_bmpinfoheader[4] = (unsigned char)(info->width);
	g_bmpinfoheader[5] = (unsigned char)(info->width >> 8);
	g_bmpinfoheader[6] = (unsigned char)(info->width >> 16);
	g_bmpinfoheader[7] = (unsigned char)(info->width >> 24);
	g_bmpinfoheader[8] = (unsigned char)(info->height);
	g_bmpinfoheader[9] = (unsigned char)(info->height >> 8);
	g_bmpinfoheader[10] = (unsigned char)(info->height >> 16);
	g_bmpinfoheader[11] = (unsigned char)(info->height >> 24);
}

void	make_bmp(t_info *info)
{
	int				fd;
	unsigned char	*img;
	int				filesize;
	int				i;

	filesize = 54 + 3 * info->width * info->height;
	img = (unsigned char *)malloc(3 * info->width * info->height);
	ft_memset(img, 0, 3 * info->width * info->height);
	loop_set(info, img);
	set_header(filesize, info);
	fd = open("img.bmp", O_CREAT | O_WRONLY | O_TRUNC);
	write(fd, g_bmpfileheader, 14);
	write(fd, g_bmpinfoheader, 40);
	i = 0;
	while (i < info->height)
	{
		write(fd, img + (info->width * (info->height - i - 1) * 3),
		3 * info->width);
		write(fd, g_bmppad, (4 - (info->width * 3) % 4) % 4);
		i++;
	}
	free(img);
	close(fd);
	free_close(info);
}
