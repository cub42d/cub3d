/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 07:15:17 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/23 17:06:00 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>

static void	read_file(t_map *map, t_parse *temp)
{
	temp->width = ft_strlen(temp->str);
	if (temp->width == 0 && map->height == 0)
		ft_free((void **)&(temp->str));
	else if (temp->width > 0)
	{
		if (map->height >= temp->size)
		{
			temp->size <<= 1;
			temp->prv = ft_malloc(sizeof(char *) * (temp->size));
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
	t_parse	*temp;

	temp = ft_calloc(sizeof(t_parse));
	temp->size = 2;
	temp->arr = ft_malloc(sizeof(char *) * temp->size);
	while (1)
	{
		temp->gnl_ret = get_next_line(file, &temp->str);
		if (!temp->str)
			break ;
		else
			read_file(map, temp);
	}
}
