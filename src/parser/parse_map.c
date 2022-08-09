/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 07:15:17 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/09 19:32:46 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>

static void	check_grid(t_map *map, int x, int y)
{
	if (((0 < x)
			&& !ft_strchr("1 ", map->arr[y][x - 1]))
	|| ((0 < y)
		&& !ft_strchr("1 ", map->arr[y - 1][x]))
	|| ((x + 1 < map->width)
		&& !ft_strchr("1 ", map->arr[y][x + 1]))
	|| ((y + 1 < map->height)
		&& !ft_strchr("1 ", map->arr[y + 1][x]))
	|| ((0 < x && 0 < y)
		&& !ft_strchr("1 ", map->arr[y - 1][x - 1]))
	|| ((x + 1 < map->width && 0 < y)
		&& !ft_strchr("1 ", map->arr[y - 1][x + 1]))
	|| ((0 < x && y + 1 < map->height)
		&& !ft_strchr("1 ", map->arr[y + 1][x - 1]))
	|| ((x + 1 < map->width && y + 1 < map->height)
		&& !ft_strchr("1 ", map->arr[y + 1][x + 1])))
		ft_error_exit(MAP_ERROR);
}

static void	check_player(t_map *map, t_parse *temp)
{
	if (map->p_pos)
		ft_error_exit(MAP_ERROR);
	map->p_pos = map->arr[temp->y][temp->x];
	map->p_y = temp->y;
	map->p_x = temp->x;
	if (map->arr[temp->y][temp->x] == 'E')
		map->p_pos = POS_E;
	else if (map->arr[temp->y][temp->x] == 'W')
		map->p_pos = POS_W;
	else if (map->arr[temp->y][temp->x] == 'S')
		map->p_pos = POS_S;
	else if (map->arr[temp->y][temp->x] == 'N')
		map->p_pos = POS_N;
	map->arr[temp->y][temp->x] = '0';
}

static void	check_map(t_map *map, t_parse *temp)
{
	while (temp->y < map->height)
	{
		temp->x = 0;
		while (temp->x < ft_strlen(temp->arr[temp->y]))
		{
			if (ft_strchr("024EWSN", map->arr[temp->y][temp->x]))
			{
				if (!temp->x || !temp->y \
					||temp->x == map->width - 1 || temp->y == map->height -1)
					ft_error_exit(MAP_ERROR);
				else if (ft_strchr("EWSN", map->arr[temp->y][temp->x]))
					check_player(map, temp);
				if (map->arr[temp->y][temp->x] == '4')
					map->sprite_cnt += 1;
			}
			else if (map->arr[temp->y][temp->x] == ' ')
				check_grid(map, temp->x, temp->y);
			else if (!ft_strchr("1", map->arr[temp->y][temp->x]))
				ft_error_exit(MAP_ERROR);
			temp->x++;
		}
		temp->y++;
	}
	if (!map->p_pos)
		ft_error_exit(MAP_ERROR);
}

static void	get_map(t_map *map, t_parse *temp)
{
	temp->width = ft_strlen(temp->str);
	if (temp->width == 0 && map->height == 0)
		ft_free((void **)&(temp->str));
	else if (temp->width > 0)
	{
		if (map->height >= temp->size)
		{
			temp->size <<= 1;
			temp->prv = ft_calloc(sizeof(char *) * (temp->size));
			ft_memcpy(temp->prv, temp->arr, (map->height * sizeof(char *)));
			free(temp->arr);
			temp->arr = temp->prv;
		}
		temp->arr[(map->height)++] = temp->str;
		temp->str = NULL;
		if (temp->width > map->width)
			map->width = temp->width;
	}
	else if (temp->width == 0 && map->height > 0)
		ft_error_exit(MAP_ERROR);
}

void	parse_map(t_map *map, int file)
{
	int		i;
	t_parse	*temp;

	temp = ft_calloc(sizeof(t_parse));
	temp->size = 2;
	temp->arr = ft_malloc(sizeof(char *) * temp->size);
	while (1)
	{
		get_next_line(file, &temp->str);
		if (!temp->str)
			break ;
		else
			get_map(map, temp);
	}
	i = -1;
	map->arr = ft_calloc(sizeof(char *) * (map->height + 1));
	while (++i < map->height)
	{
		map->arr[i] = ft_calloc(sizeof(char) * (map->width + 1));
		ft_memcpy(map->arr[i], temp->arr[i], ft_strlen(temp->arr[i]));
	}
	check_map(map, temp);
	ft_double_free(&(temp->arr));
	ft_free((void **)&temp);
}
