/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 01:20:17 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 21:41:55 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kub.h"

void	set_splited_line(char **tmp_ret, char *start, int len, t_info *info)
{
	int i;

	if (!(*tmp_ret = malloc(sizeof(char) * (len + 1))))
		error(6, info);
	i = 0;
	while (i < len && start[i] != '\0')
	{
		(*tmp_ret)[i] = start[i];
		i++;
	}
	(*tmp_ret)[len] = '\0';
}

int		set_floor(char *line, t_info *info)
{
	char **splited_line;

	splited_line = NULL;
	splited_line = ft_split(line, " ,", info);
	if (get_word_count(splited_line, 1) != 4 || ft_memcmp(splited_line[0], \
	"F", 2) || info->cub_flags[6] || info->cub_flags[8])
	{
		ft_strsfree(splited_line);
		error(4, info);
	}
	info->floor = ft_atoi(splited_line[1]) << 16 | ft_atoi(splited_line[2]) \
	<< 8 | ft_atoi(splited_line[3]);
	ft_strsfree(splited_line);
	info->cub_flags[6] = 1;
	return (1);
}

int		set_ceiling(char *line, t_info *info)
{
	char **splited_line;

	splited_line = NULL;
	splited_line = ft_split(line, " ,", info);
	if (get_word_count(splited_line, 1) != 4 || ft_memcmp(splited_line[0], \
	"C", 2) || info->cub_flags[7] || info->cub_flags[8])
	{
		ft_strsfree(splited_line);
		error(4, info);
	}
	info->ceiling = ft_atoi(splited_line[1]) << 16 | ft_atoi(splited_line[2]) \
	<< 8 | ft_atoi(splited_line[3]);
	ft_strsfree(splited_line);
	info->cub_flags[7] = 1;
	return (1);
}

int		get_settings(char *line, t_info *info)
{
	if (line[0] == '\0' && !info->cub_flags[8])
		return (0);
	else if (line[0] == '\0' && info->cub_flags[8])
		error(4, info);
	else if (line[0] == 'R')
		return (set_resolution(line, info));
	else if (line[0] == 'N')
		return (set_north(line, info));
	else if (line[0] == 'S' && line[1] == 'O')
		return (set_south(line, info));
	else if (line[0] == 'W')
		return (set_west(line, info));
	else if (line[0] == 'E')
		return (set_east(line, info));
	else if (line[0] == 'S')
		return (set_sprite(line, info));
	else if (line[0] == 'F')
		return (set_floor(line, info));
	else if (line[0] == 'C')
		return (set_ceiling(line, info));
	set_map(line, info);
	return (0);
}
