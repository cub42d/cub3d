/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 07:15:17 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/23 18:00:19 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>

static void	get_map(t_map *map, t_parse *temp)
{
	// 읽은 줄의 길이를 구함
	temp->width = ft_strlen(temp->str);
	// 길이가 0 즉 gnl이 읽은게 개행, 그리고 아직 arr에 하나도 저장을 안하면 free하고 돌아감
	if (temp->width == 0 && map->height == 0)
		ft_free((void **)&(temp->str));
	// 길이가 있음 그러면 배열에 넣음
	else if (temp->width > 0)
	{
		// 동적할당같은 정적할당 배열
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
	// 길이가 0이고 배열에 데이터가 들어가 있으면 중간에 개행을 만난거니까 파일 오류
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
		// gnl 오류는 gnl 내부에서 바로 exit
		temp->gnl_ret = get_next_line(file, &temp->str);
		// file의 eof(temp->str == NULL)이면 while break
		if (!temp->str)
			break ;
		// temp->str이 NULL이 아님
		else
			get_map(map, temp);
	}
}
