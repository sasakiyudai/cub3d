/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 01:10:37 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 21:42:43 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

char	**g_ret = NULL;
int		g_len = 0;
char	*g_start = NULL;

int		ft_initialize(char *str, char *charset, t_info *info)
{
	int word;

	word = 0;
	while (*str != '\0')
	{
		if (ft_ischarset(*str, charset))
		{
			if (g_len > 0)
				word++;
			g_len = 0;
		}
		else
			g_len++;
		str++;
	}
	if (g_len > 0)
		word++;
	if (!(g_ret = malloc(sizeof(char*) * (word + 1))))
		error(6, info);
	if (g_ret == 0)
		return (-1);
	g_ret[word] = 0;
	if (word == 0)
		return (-1);
	return (0);
}

char	**ft_split(char *str, char *charset, t_info *info)
{
	char **tmp_ret;

	tmp_ret = NULL;
	if (ft_initialize(str, charset, info) != 0)
		return (g_ret);
	g_len = 0;
	tmp_ret = g_ret;
	g_start = str;
	while (*str != '\0')
	{
		if (ft_ischarset(*str, charset))
		{
			if (g_len > 0)
				set_splited_line(tmp_ret++, g_start, g_len, info);
			g_len = 0;
		}
		else if (g_len++ == 0)
			g_start = str;
		str++;
	}
	if (g_len > 0)
		set_splited_line(tmp_ret, g_start, g_len, info);
	return (g_ret);
}

void	read_cub(char *path, t_info *info)
{
	char	*line;
	int		flag;
	int		fd;

	line = NULL;
	init_checkmap(info);
	fd = open(path, 0);
	while ((flag = get_next_line(fd, &line)) >= 0)
	{
		get_settings(line, info);
		free(line);
		if (flag == 0)
			break ;
	}
	if (info->flag.player_flag == 0)
		error(4, info);
	if (flag == -1)
		error(3, info);
	fill_map(info->posx + 1, info->posy + 1, info);
	check_map(info);
	set_sprites(info);
	close(fd);
}
