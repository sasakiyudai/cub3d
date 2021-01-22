/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_save.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 23:23:02 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 00:24:32 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

char	*g_save = NULL;

int		ft_put_line(char **line, char *buf)
{
	int		flag;
	size_t	n;
	char	*tmp;

	n = ft_strchr(buf, '\n');
	if (!(tmp = ft_strjoin(*line, buf, -1, n)))
		return (-1);
	free(*line);
	*line = tmp;
	tmp = NULL;
	flag = 0;
	if (buf[n] == '\n')
	{
		if (!(tmp = ft_strdup(buf + n + 1)))
			return (-1);
		flag = 1;
	}
	free(g_save);
	g_save = tmp;
	return (flag);
}

void	free_free(char **line)
{
	free(g_save);
	g_save = NULL;
	free(*line);
}

int		get_next_line(int fd, char **line)
{
	int			flag;
	char		*buf;
	ssize_t		n;

	if (fd < 0 || line == NULL || !(*line = malloc(1)))
		return (-1);
	*line[0] = 0;
	flag = 0;
	if (g_save)
		flag = ft_put_line(line, g_save);
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		flag = -1;
	while (flag == 0 && (n = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[n] = 0;
		flag = ft_put_line(line, buf);
	}
	free(buf);
	if (flag == -1)
		free_free(line);
	if (n == -1)
		return (-1);
	return (flag);
}

int		free_close(t_info *info)
{
	int i;

	if (info->flag.save_flag == 0)
		mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_image(info->mlx, info->img.img);
	i = 0;
	while (i < 5)
		free(info->texture[i++]);
	free(info->spriteorder);
	free(info->spritedistance);
	free(info->zbuffer);
	free(info->sprite);
	free(g_save);
	i = 0;
	while (i < info->height)
		free(info->buf[i++]);
	free(info->buf);
	exit(0);
}

void	only_for_seven(t_info *info)
{
	int i;

	i = 0;
	write(2, "Invalid texture\n", 16);
	while (i < info->tex_index)
		free(info->texture[i++]);
	i = 0;
	while (i < info->height)
		free(info->buf[i++]);
	free(info->buf);
	free(info->spriteorder);
	free(info->spritedistance);
	free(info->zbuffer);
	free(g_save);
	exit(1);
}
