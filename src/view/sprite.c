/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:39:59 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/08/05 21:36:07 by hyunkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static int	compare_sprites(const void *a, const void *b)
{
	if (((t_sprite *)a)->dist > ((t_sprite *)b)->dist)
		return (-1);
	else
		return (1);
}

t_sprite	*get_visible_sprites(t_view *vu, t_map *map)
{
	int			n;
	int			x;
	int			y;
	t_sprite	*sprite;

	n = 0;
	sprite = NULL;
	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (vu->visible[x][y] == 0 || map_get_cell(map, x, y) != 4)
			{
				y++;
				continue;
			}
			if (n == 0)
				sprite = ft_calloc(sizeof(t_sprite));
			/* 일단 realloc을 써봄 */
			else
				sprite = realloc(sprite, sizeof(t_sprite) * (n + 1));
			sprite[n].tex = vu->tex_wall[5];
			sprite[n].x = x;
			sprite[n].y = y;
			sprite[n].theta = atan2((y + 0.5) - vu->p_y, (x + 0.5) - vu->p_x);
			if (sprite[n].theta < 0)
				sprite[n].theta += _2PI;
			sprite[n].dist = \
			ft_l2dist(vu->p_x, vu->p_y, x + 0.5, y + 0.5 * cos(vu->theta - sprite[n].theta));
			n++;
			y++;
		}
		x++;
	}
	vu->pcnt = n;
	return (sprite);
}

void	draw_sprite(t_view *vu, t_map *map)
{
	int			nsp;
	t_sprite	*sprite;
	int			i;
	int			sprite_height;
	double		angle;
	double		fov_h;
	int			cx;
	int			x_min;
	int			x_max;
	int			x;

	nsp = 0;
	sprite = get_visible_sprites(vu, map);
	fov_h = ft_deg2rad(FOV);
	/* 일단 stdlib에 있는 qsort를 쓰겠습니다;; */
	qsort(sprite, nsp, sizeof(t_sprite), compare_sprites);
	i = 0;
	while (i < nsp)
	{
		sprite_height = get_wall_height(sprite[i].dist);
		angle = sprite[i].theta - vu->theta;
		if (angle > M_PI)
			angle -= _2PI;
		else if (angle < -M_PI)
			angle += _2PI;
		cx = (int)((fov_h - angle) * ((SX - .1) / fov_h));
		x_min = ft_max(0, cx - sprite_height / 2);
		x_max = ft_min(SX, cx + sprite_height / 2);
		x = x_min;
		while (x < x_max)
		{
			if (sprite[i].dist > vu->z_buf[x])
			{
				x++;
				continue;
			}
			double	texture_ratio;
			texture_ratio = (double)(x - cx)/sprite_height + 0.5;
			int	texture_x;
			texture_x = (int)(texture_ratio * sprite[i].tex.px_wid);
			int	y0;
			y0 = (int)((SY - sprite_height) / 2.0);
			int	y;
			y = ft_max(0, y0);
			while (y < ft_min(SY, y0 + sprite_height))
			{
				int	texture_y;
				texture_y = (int)((double)(y - y0) * sprite[i].tex.px_hei / sprite_height);
				int	color;
				color = get_wall_texture(&sprite[i].tex, texture_x, texture_y);
				put_pixel(vu, x, y, color);
				y++;
			}
			x++;
		}
		i++;
	}
	if (nsp > 0)
		free(sprite);
}
