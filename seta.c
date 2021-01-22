/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 01:15:08 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 21:20:21 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

int		set_north(char *line, t_info *info)
{
	char **splited_line;

	splited_line = NULL;
	splited_line = ft_split(line, " ", info);
	if (get_word_count(splited_line, 0) != 2 || ft_memcmp(splited_line[0], \
	"NO", 3) || info->cub_flags[1] || info->cub_flags[8])
	{
		ft_strsfree(splited_line);
		error(4, info);
	}
	info->path.north = ft_strdup(splited_line[1]);
	ft_strsfree(splited_line);
	info->cub_flags[1] = 1;
	return (1);
}

int		set_south(char *line, t_info *info)
{
	char **splited_line;

	splited_line = NULL;
	splited_line = ft_split(line, " ", info);
	if (get_word_count(splited_line, 0) != 2 || ft_memcmp(splited_line[0], \
	"SO", 3) || info->cub_flags[2] || info->cub_flags[8])
	{
		ft_strsfree(splited_line);
		error(4, info);
	}
	info->path.south = ft_strdup(splited_line[1]);
	ft_strsfree(splited_line);
	info->cub_flags[2] = 1;
	return (1);
}

int		set_west(char *line, t_info *info)
{
	char **splited_line;

	splited_line = NULL;
	splited_line = ft_split(line, " ", info);
	if (get_word_count(splited_line, 0) != 2 || ft_memcmp(splited_line[0], \
	"WE", 3) || info->cub_flags[3] || info->cub_flags[8])
	{
		ft_strsfree(splited_line);
		error(4, info);
	}
	info->path.west = ft_strdup(splited_line[1]);
	ft_strsfree(splited_line);
	info->cub_flags[3] = 1;
	return (1);
}

int		set_east(char *line, t_info *info)
{
	char **splited_line;

	splited_line = NULL;
	splited_line = ft_split(line, " ", info);
	if (get_word_count(splited_line, 0) != 2 || ft_memcmp(splited_line[0], \
	"EA", 3) || info->cub_flags[4] || info->cub_flags[8])
	{
		ft_strsfree(splited_line);
		error(4, info);
	}
	info->path.east = ft_strdup(splited_line[1]);
	ft_strsfree(splited_line);
	info->cub_flags[4] = 1;
	return (1);
}

int		set_sprite(char *line, t_info *info)
{
	char **splited_line;

	splited_line = NULL;
	splited_line = ft_split(line, " ", info);
	if (get_word_count(splited_line, 0) != 2 || ft_memcmp(splited_line[0], \
	"S", 2) || info->cub_flags[5] || info->cub_flags[8])
	{
		ft_strsfree(splited_line);
		error(4, info);
	}
	info->path.splite = ft_strdup(splited_line[1]);
	ft_strsfree(splited_line);
	info->cub_flags[5] = 1;
	return (1);
}
