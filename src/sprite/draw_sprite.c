/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:29:10 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 01:06:35 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "utils.h"
#include <math.h>

static int	get_pivot(t_sprite *sp, int start, int end)
{
	int			i;
	int			j;
	t_sprite	temp;
	double		pivot;

	pivot = sp[end].dist;
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (sp[j].dist <= pivot)
		{
			temp = sp[++i];
			sp[i] = sp[j];
			sp[j] = temp;
		}
		j++;
	}
	temp = sp[i + 1];
	sp[i + 1] = sp[end];
	sp[end] = temp;
	return (i + 1);
}

static void	_qsort(t_sprite *sp, int start, int end)
{
	double	pivot;

	if (start < end)
	{
		pivot = get_pivot(sp, start, end);
		_qsort(sp, start, pivot - 1);
		_qsort(sp, pivot + 1, end);
	}
}

static void	get_visible_sprite(t_view *vu, t_map *map)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = -1;
	while (++x < map->height)
	{
		y = -1;
		while (++y < map->width)
		{
			if (map->arr[x][y] == '4')
			{
				vu->sprite[i].x = x;
				vu->sprite[i].y = y;
				vu->sprite[i].theta = atan2((y + 0.5) - vu->p_y, \
				(x + 0.5) - vu->p_x);
				if (vu->sprite[i].theta < 0)
					vu->sprite[i].theta += _2PI;
				vu->sprite[i].dist = ft_l2dist(vu->p_x, vu->p_y, \
				x + 0.5, y + 0.5) * cos(vu->theta - vu->sprite[i].theta);
				i++;
			}
		}
	}
}

static void	put_sprite(t_view *vu)
{
	int	x;
	int	y;
	int	color;

	x = vu->utils.x_min;
	while (++x < vu->utils.x_max)
	{
		if (vu->sprite[vu->utils.i].dist > vu->zbuf[x] \
		|| vu->sprite[vu->utils.i].dist < 0.5)
			continue ;
		vu->utils.txratio = (double)(x - vu->utils.cx) / vu->utils.sh + 0.5;
		vu->utils.tx = (int)(vu->utils.txratio * 64);
		vu->utils.y0 = (int)((SY - vu->utils.sh) / 2.0);
		y = ft_max(0, vu->utils.y0) - 1;
		while (++y < ft_min(SY, vu->utils.y0 + vu->utils.sh))
		{
			vu->utils.ty = (int)((double)(y - vu->utils.y0) * 64 \
			/ vu->utils.sh);
			color = get_wall_texture(&vu->tex_wall[5], vu->utils.tx, \
			vu->utils.ty);
			if (color >= 0)
				put_pixel(vu, x, y, color);
		}
	}
}

void	draw_sprite(t_view *vu, t_map *map)
{
	if (map->sprite_cnt > 0)
	{
		vu->sprite = ft_calloc(sizeof(t_sprite) * map->sprite_cnt);
		get_visible_sprite(vu, map);
		_qsort(vu->sprite, 0, map->sprite_cnt);
		vu->utils.i = map->sprite_cnt + 1;
		while (--vu->utils.i >= 0)
		{
			vu->utils.sh = get_wall_height(vu->sprite[vu->utils.i].dist);
			vu->utils.angle = vu->sprite[vu->utils.i].theta - vu->theta;
			ft_colision_angle(&(vu->utils.angle));
			vu->utils.cx = (int)((vu->fovh_2 - vu->utils.angle) \
			* ((SX - 1.) / ft_deg2rad(FOV)));
			vu->utils.x_min = ft_max(0, vu->utils.cx - vu->utils.sh / 2) - 1;
			vu->utils.x_max = ft_min(SX, vu->utils.cx + vu->utils.sh / 2);
			put_sprite(vu);
		}
	}
}
