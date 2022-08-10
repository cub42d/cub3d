/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:29:10 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 19:38:06 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "utils.h"
#include <math.h>

static void	_qsort(t_sprite *sp, int start, int end)
{
	t_sprite	temp;
	double		pivot;
	int			i;
	int			j;

	if (start < end)
	{
		pivot = sp[end].dist;
		i = start - 1;
		j = start - 1;
		while (++j < end)
		{
			if (sp[j].dist <= pivot)
			{
				temp = sp[++i];
				sp[i] = sp[j];
				sp[j] = temp;
			}
		}
		temp = sp[i + 1];
		sp[i + 1] = sp[end];
		sp[end] = temp;
		_qsort(sp, start, i);
		_qsort(sp, i + 2, end);
	}
}

static void	set_sprite_texture(t_view *vu, int *color, int tx, int ty)
{
	if (0 <= vu->loop && vu->loop <= 5)
		*color = get_wall_texture(&vu->tex_wall[5], tx, ty);
	else if (6 <= vu->loop && vu->loop <= 10)
		*color = get_wall_texture(&vu->tex_wall[6], tx, ty);
	else if (11 <= vu->loop && vu->loop <= 15)
		*color = get_wall_texture(&vu->tex_wall[7], tx, ty);
	else if (16 <= vu->loop && vu->loop <= 20)
		*color = get_wall_texture(&vu->tex_wall[8], tx, ty);
	else if (21 <= vu->loop && vu->loop <= 25)
		*color = get_wall_texture(&vu->tex_wall[9], tx, ty);
	else if (26 <= vu->loop && vu->loop <= 30)
		*color = get_wall_texture(&vu->tex_wall[10], tx, ty);
	else if (31 <= vu->loop && vu->loop <= 35)
		*color = get_wall_texture(&vu->tex_wall[11], tx, ty);
	else if (36 <= vu->loop && vu->loop <= 40)
		*color = get_wall_texture(&vu->tex_wall[12], tx, ty);
	else if (41 <= vu->loop && vu->loop <= 45)
		*color = get_wall_texture(&vu->tex_wall[13], tx, ty);
	else if (46 <= vu->loop && vu->loop <= 50)
	{
		*color = get_wall_texture(&vu->tex_wall[14], tx, ty);
		vu->flag = 1;
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
			set_sprite_texture(vu, &color, vu->utils.tx, vu->utils.ty);
			if (color >= 0)
				put_pixel(vu, x, y, color);
		}
	}
}

static void	get_visible_sprite(t_view *vu, t_map *map)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	x = -1;
	while (++x < map->height)
	{
		y = -1;
		while (++y < map->width)
		{
			if (map->arr[x][y] == '4')
			{
				vu->sprite[++i].x = x;
				vu->sprite[i].y = y;
				vu->sprite[i].theta = atan2((y + 0.5) - vu->p_y, \
				(x + 0.5) - vu->p_x);
				if (vu->sprite[i].theta < 0)
					vu->sprite[i].theta += _2PI;
				vu->sprite[i].dist = ft_l2dist(vu->p_x, vu->p_y, \
				x + 0.5, y + 0.5) * cos(vu->theta - vu->sprite[i].theta);
			}
		}
	}
}

void	draw_sprite(t_view *vu, t_map *map)
{
	if (map->sprite_cnt > 0)
	{
		get_visible_sprite(vu, map);
		_qsort(vu->sprite, 0, map->sprite_cnt);
		vu->utils.i = map->sprite_cnt;
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
