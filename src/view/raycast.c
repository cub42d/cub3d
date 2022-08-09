/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:50:49 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 00:43:12 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "utils.h"
#include <math.h>

static int	assist_intersection(t_map *map, t_view *vu, t_dda *dda, int *is_hit)
{
	int	cell;

	cell = map_get_cell(map, dda->map_x, dda->map_y);
	if (cell < 0)
		return (0);
	if (cell == 1 || cell == 2)
	{
		get_ray_wall_var(vu, dda);
		if (cell == 2)
			vu->is_door = TRUE;
		else
			vu->is_door = FALSE;
		*is_hit = TRUE;
		return (0);
	}
	if (dda->hit_side == VERT)
		dda->nx += dda->delta_x;
	else
		dda->ny += dda->delta_y;
	return (1);
}

static int	get_wall_intersection(t_view *vu, t_map *map, double ray)
{
	t_dda	dda;
	int		is_hit;

	init_dda(vu, &dda, ray);
	is_hit = FALSE;
	while (1)
	{
		get_map_x_y(vu, &dda);
		if (!assist_intersection(map, vu, &dda, &is_hit))
			break ;
	}
	return (is_hit);
}

double	cast_single_ray(t_view *vu, t_map *map, int x, double theta)
{
	double	angle_per_pixel;
	double	fovh_2;
	double	ray;

	angle_per_pixel = ft_deg2rad(FOV) / (SX - 1.);
	fovh_2 = ft_deg2rad(FOV) / 2.0;
	ray = (theta + fovh_2) - (x * angle_per_pixel);
	if (get_wall_intersection(vu, map, ray) == FALSE)
		return (INFINITY);
	vu->wl.wall_dist = ft_l2dist(vu->p_x, vu->p_y, \
	vu->wl.wall_x, vu->wl.wall_y);
	vu->wl.wall_dist *= cos(theta - ray);
	vu->zbuf[x] = vu->wl.wall_dist;
	return (vu->wl.wall_dist);
}
