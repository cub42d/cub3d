/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:29:10 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/09 22:23:32 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "utils.h"
#include <math.h>

static void	change_value(t_sprite *s1, t_sprite *s2)
{
	t_sprite	temp;

	temp.x = s1->x;
	temp.y = s1->y;
	temp.dist = s1->dist;
	temp.theta = s1->theta;
	temp.sh = s1->sh;
	s1->x = s2->x;
	s1->y = s2->y;
	s1->dist = s2->dist;
	s1->theta = s2->theta;
	s1->sh = s2->sh;
	s2->x = temp.x;
	s2->y = temp.y;
	s2->dist = temp.dist;
	s2->theta = temp.theta;
	s2->sh = temp.sh;
}

static void	sort_sprite(t_view *vu, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->sprite_cnt - 1)
	{
		j = i;
		while (++j < map->sprite_cnt)
		{
			if (vu->sprite[j].dist < vu->sprite[i].dist)
				change_value(&(vu->sprite[i]), &(vu->sprite[j]));
		}
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
			if (vu->visible[x][y] != '1')
				continue ;
			if (map->arr[x][y] == '4')
			{
				vu->sprite[i].x = x;
				vu->sprite[i].y = y;
				vu->sprite[i].theta = atan2((y + 0.5) - vu->p_y, (x + 0.5) - vu->p_x);
				vu->sprite[i].sh = get_wall_height(vu->sprite[i].dist);
				if (vu->sprite[i].theta < 0)
					vu->sprite[i].theta += _2PI;
				vu->sprite[i].dist = ft_l2dist(vu->p_x, vu->p_y, x + 0.5, y + 0.5) * cos(vu->theta - vu->sprite[i].theta);
				i++;
			}
		}
	}
}

void	draw_sprite(t_view *vu, t_map *map)
{
	int		i;
	int		cx;
	int		x;
	double	angle;
	double	tex_ratio;
	double	tex_x;
	int		y0;
	int		y;
	int		tex_y;
	int		color;

	get_visible_sprite(vu, map);
	sort_sprite(vu, map);
	i = -1;
	while (++i < map->sprite_cnt)
	{
		angle = vu->sprite[i].theta - vu->theta;
		ft_colision_angle(&angle);
		cx = (int)((vu->fov_h - angle) * ((SX - .1) / vu->fov_h));
		x = ft_max(0, cx - vu->sprite[i].sh / 2) - 1;
		while (++x < ft_min(SX, cx + vu->sprite[i].sh / 2))
		{
			if (vu->sprite[i].dist > vu->zbuf[x])
				continue ;
			tex_ratio = (double)(x - cx) / vu->sprite[i].sh + 0.5;
			tex_x = (int)(tex_ratio * 64);
			y0 = (int)((SY - vu->sprite[i].sh) / 2.0);
			y = ft_max(0, y0) -1;
			while (++y < ft_min(SY, y0 + vu->sprite[i].sh))
			{
				tex_y = (int)((double)(y - y0) * 64 / vu->sprite[i].sh);
				color = get_wall_texture(&vu->tex_wall[5], tex_x, tex_y);
				if (color >= 0)
					put_pixel(vu, x, y, color);
			}
		}
	}
}

void	init_sprite(t_view *vu, t_map *map)
{
	int	i;

	i = -1;
	if (map->sprite_cnt > 0)
	{
		vu->visible = ft_calloc(sizeof(char *) * map->height + 1);
		while (++i < map->height)
			vu->visible[i] = ft_calloc(sizeof(char) * map->width + 1);
		vu->sprite = ft_calloc(sizeof(t_sprite) * map->sprite_cnt);
	}
}
