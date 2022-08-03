/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:39:59 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/08/03 20:48:27 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "util.h"
#include <math.h>

static int	compare_sprites(void *a, void *b)
{
	if (((t_sprite *)a)->dist > ((t_sprite *)b)->dist)
		return (-1);
	else
		return (1);
}

t_sprite	*get_visible_sprites(t_view *vu, t_map *map);
/*
	여기에 함수 내용 입력. t_player *pp 이게 뭔지 모르겠음.
	argument로 들어오는 pcnt도 뭔지 모르겠음.
 */
