/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 01:17:54 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 01:20:07 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	set_for_west(t_info *info, char c)
{
	if (c == 'E')
	{
		info->dirx = 0.01;
		info->diry = 0.99994999875;
		info->planex = 0.65992423807;
		info->planey = 0.01;
	}
	else if (c == 'W')
	{
		info->dirx = 0.01;
		info->diry = -0.99994999875;
		info->planex = -0.65992423807;
		info->planey = 0.01;
	}
}

void	ft_strsfree(char **strs)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = strs;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(tmp);
}

int		get_word_count(char **splited, int onef_twor)
{
	int i;

	i = 0;
	while (splited[i])
	{
		if (onef_twor == 1 && (i == 1 || i == 2 || i == 3))
			if (0 > ft_atoi(splited[i]) || ft_atoi(splited[i]) > 255)
				return (-1);
		if (onef_twor == 2 && (i == 1 || i == 2))
			if (ft_atoi(splited[i]) <= 0)
				return (-1);
		i++;
	}
	return (i);
}

int		set_resolution(char *line, t_info *info)
{
	char	**splited_line;
	int		screen_width;
	int		screen_height;

	splited_line = NULL;
	mlx_get_screen_size(info->mlx, &screen_width, &screen_height);
	splited_line = ft_split(line, " ", info);
	if (get_word_count(splited_line, 2) != 3 || ft_memcmp(splited_line[0], \
	"R", 2) || info->cub_flags[0] || info->cub_flags[8])
	{
		ft_strsfree(splited_line);
		error(4, info);
	}
	info->width = (ft_atoi(splited_line[1]) > screen_width) ? \
	screen_width : ft_atoi(splited_line[1]);
	info->height = (ft_atoi(splited_line[2]) > screen_height) ? \
	screen_height : ft_atoi(splited_line[2]);
	ft_strsfree(splited_line);
	info->cub_flags[0] = 1;
	return (1);
}
