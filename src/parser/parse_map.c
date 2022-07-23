/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 07:15:17 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/23 10:34:05 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>

static void	read_file(t_map *map, t_parse *temp, int file)
{
	while (1)
	{
		temp->ret = get_next_line(file, &temp->str);
		temp->width = ft_strlen(temp->str);
		if (temp->width == 0 && temp->ret == 0)
			break ;
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
		else if (temp->width == 0)
			ft_free((void **)&(temp->str));
	}
}

void	parse_map(t_map *map, int file)
{
	t_parse	*temp;

	temp = ft_calloc(sizeof(t_parse));
	temp->size = 2;
	temp->arr = ft_malloc(sizeof(char *) * temp->size);
	read_file(map, temp, file);

}
