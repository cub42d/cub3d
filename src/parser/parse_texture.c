/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:32:24 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/28 02:20:59 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "macro.h"
#include "utils.h"

static void	free_line(char **line, char ***temp)
{
	ft_free((void **) line);
	ft_double_free(temp);
}

static int	get_color(char *line)
{
	int		i;
	int		ret;
	char	*temp;

	ret = 0;
	i = -1;
	if (!line)
		ft_error_exit(MAP_ERROR);
	temp = ft_strtrim(line, " ,\t\n");
	while (temp[++i])
	{
		if (!('0' <= temp[i] && temp[i] <= '9'))
			ft_error_exit(MAP_ERROR);
		ret *= 10;
		ret += temp[i] - '0';
		if (ret > 255)
			ft_error_exit(MAP_ERROR);
	}
	ft_free((void **) &temp);
	return (ret);
}

static int	parse_color(char **line)
{
	int	r;
	int	g;
	int	b;

	r = get_color(line[1]);
	g = get_color(line[2]);
	b = get_color(line[3]);
	if (line[4])
		ft_error_exit(MAP_ERROR);
	return ((r << 16) + (g << 8) + b);
}

static void	get_texture(t_map *map, char *line, char **temp)
{
	int	cnt;

	cnt = 0;
	while (*line)
	{
		if (*line == ',')
			++cnt;
		++line;
	}
	if (ft_iseq(temp[0], NORTH) && !temp[2])
		map->no = ft_strdup(temp[1]);
	else if (ft_iseq(temp[0], SOUTH) && !temp[2])
		map->so = ft_strdup(temp[1]);
	else if (ft_iseq(temp[0], EAST) && !temp[2])
		map->ea = ft_strdup(temp[1]);
	else if (ft_iseq(temp[0], WEST) && !temp[2])
		map->we = ft_strdup(temp[1]);
	else if (ft_iseq(temp[0], FLOOR) && (cnt == 2))
		map->f = parse_color(temp);
	else if (ft_iseq(temp[0], CELLING) && (cnt == 2))
		map->c = parse_color(temp);
	else
		ft_error_exit(MAP_ERROR);
}

void	parse_texture(t_map *map, int file)
{
	int		i;
	char	*line;
	char	**temp;

	i = 0;
	while (i < 6)
	{
		get_next_line(file, &line);
		if (!line)
			ft_error_exit(MAP_ERROR);
		temp = ft_split(line, ", \n");
		if (!*temp)
		{
			free_line(&line, &temp);
			continue ;
		}
		if (!temp[1])
			ft_error_exit(MAP_ERROR);
		get_texture(map, line, temp);
		free_line(&line, &temp);
		i++;
	}
}
