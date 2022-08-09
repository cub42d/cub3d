/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 01:50:05 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 01:04:39 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include <math.h>

static double	get_next_coord(int delta, \
								double next_coord, double player_coord)
{
	if (delta > 0)
		next_coord = floor(player_coord) + 1;
	else
	{
		if (delta < 0)
			next_coord = ceil(player_coord) - 1;
		else
			next_coord = player_coord;
	}
	return (next_coord);
}

int	map_get_cell(t_map *map, int x, int y)
{
	if (x >= 0 && x < map->height && y >= 0 && y < map->width)
	{
		if ((map->arr[x][y] >= '0' && map->arr[x][y] <= '2') \
		|| map->arr[x][y] == '4')
			return ((map->arr[x][y] - '0'));
		else
			return (0);
	}
	else
		return (-1);
}

void	get_map_x_y(t_view *vu, t_dda *dda)
{
	if (dda->delta_x != 0)
		dda->f_x = dda->x_slope * (dda->nx - vu->p_x) + vu->p_y;
	if (dda->delta_y != 0)
		dda->g_x = dda->y_slope * (dda->ny - vu->p_y) + vu->p_x;
	dda->dist_verti = ft_l2dist(vu->p_x, vu->p_y, dda->nx, dda->f_x);
	dda->dist_horiz = ft_l2dist(vu->p_x, vu->p_y, dda->g_x, dda->ny);
	if (dda->dist_verti < dda->dist_horiz)
	{
		if (dda->delta_x == 1)
			dda->map_x = (int)dda->nx;
		else
			dda->map_x = (int)(dda->nx - 1);
		dda->map_y = (int)dda->f_x;
		dda->hit_side = VERT;
	}
	else
	{
		dda->map_x = (int)dda->g_x;
		if (dda->delta_y == 1)
			dda->map_y = (int)dda->ny;
		else
			dda->map_y = (int)(dda->ny - 1);
		dda->hit_side = HORIZ;
	}
}

void	get_ray_wall_var(t_view *vu, t_dda *dda)
{
	if (dda->hit_side == VERT)
	{
		if (dda->delta_x > 0)
			vu->wl.wall_dir = DIR_W;
		else
			vu->wl.wall_dir = DIR_E;
		vu->wl.wall_x = dda->nx;
		vu->wl.wall_y = dda->f_x;
	}
	else
	{
		if (dda->delta_y > 0)
			vu->wl.wall_dir = DIR_S;
		else
			vu->wl.wall_dir = DIR_N;
		vu->wl.wall_x = dda->g_x;
		vu->wl.wall_y = dda->ny;
	}
}

void	init_dda(t_view *vu, t_dda *dda, double ray)
{
	dda->delta_x = ft_numsign(cos(ray));
	dda->delta_y = ft_numsign(sin(ray));
	if (dda->delta_x == 0)
		dda->x_slope = INFINITY;
	else
		dda->x_slope = tan(ray);
	if (dda->delta_y == 0)
		dda->y_slope = INFINITY;
	else
		dda->y_slope = 1. / tan(ray);
	dda->nx = get_next_coord(dda->delta_x, dda->nx, vu->p_x);
	dda->ny = get_next_coord(dda->delta_y, dda->ny, vu->p_y);
	dda->f_x = INFINITY;
	dda->g_x = INFINITY;
}
