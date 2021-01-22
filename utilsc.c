/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 13:24:47 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 21:36:10 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	set_player(t_info *info, char c, int y)
{
	info->posy = y + 0.5;
	info->posx = info->index + 0.5;
	if (c == 'N')
	{
		info->dirx = -0.99994999875;
		info->diry = 0.01;
		info->planex = 0.01;
		info->planey = 0.65992423807;
	}
	else if (c == 'S')
	{
		info->dirx = 0.99994999875;
		info->diry = 0.01;
		info->planex = 0.01;
		info->planey = -0.65992423807;
	}
	else
		set_for_west(info, c);
}

void	init_checkmap(t_info *info)
{
	int i;
	int j;

	i = 0;
	while (i < 102)
	{
		j = 0;
		while (j < 102)
		{
			if (i == 0 || j == 0 || i == 101 || j == 101)
				info->map.checkie[i][j] = 9;
			else
				info->map.checkie[i][j] = 0;
			if (0 <= i && i <= 99 && 0 <= j && j <= 99)
				info->map.world[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	sortsprites(int *order, double *dist, t_info *info)
{
	t_pair	*sprites;
	int		i;

	sprites = NULL;
	if (!(sprites = (t_pair *)malloc(sizeof(t_pair) * info->flag.numsprite)))
		error(6, info);
	i = 0;
	while (i < info->flag.numsprite)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, info->flag.numsprite);
	i = 0;
	while (i < info->flag.numsprite)
	{
		dist[i] = sprites[info->flag.numsprite - i - 1].first;
		order[i] = sprites[info->flag.numsprite - i - 1].second;
		i++;
	}
	free(sprites);
}

void	set_condition(t_info *info, int i, char *line)
{
	if (line[i] == 'N' || line[i] == 'S' || \
		line[i] == 'W' || line[i] == 'E')
	{
		if (info->flag.player_flag == 1)
			error(4, info);
		info->flag.player_flag = 1;
		set_player(info, line[i], i);
		info->map.world[info->index][i] = 0;
		info->map.checkie[info->index + 1][i + 1] = 0;
	}
	else if (line[i] != ' ')
	{
		info->map.world[info->index][i] = line[i] - '0';
		info->map.checkie[info->index + 1][i + 1] = line[i] - '0';
	}
}

void	set_map(char *line, t_info *info)
{
	int i;

	info->cub_flags[8] = 1;
	if (ft_strlen(line) > 100 || info->index > 100)
		error(5, info);
	i = 0;
	while (i < (int)ft_strlen(line))
	{
		isvalid(line[i], info);
		if (line[i] == '2')
			info->flag.numsprite++;
		set_condition(info, i, line);
		i++;
	}
	info->index++;
}
