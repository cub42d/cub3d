/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 10:33:07 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 02:52:33 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "utils.h"
#include <math.h>

static int	map_get_door(t_map *map, int x, int y)
{
	if (x >= 0 && x < map->height && y >= 0 && y < map->width)
	{
		if (map->arr[x][y] >= '0' && map->arr[x][y] <= '4')
			return ((map->arr[x][y] - '0'));
		else
			return (0);
	}
	else
		return (-1);
}

static int	get_door_intersection(t_view *vu, t_map *map, \
									t_dda *dda, double ray)
{
	int		cell;
	int		is_hit;

	init_dda(vu, dda, ray);
	is_hit = FALSE;
	while (!is_hit)
	{
		get_map_x_y(vu, dda);
		cell = map_get_door(map, dda->map_x, dda->map_y);
		if (cell < 0)
			break ;
		if (cell == 2 || cell == 3)
		{
			get_ray_wall_var(vu, dda);
			is_hit = TRUE;
		}
		if (dda->hit_side == VERT)
			dda->nx += dda->delta_x;
		else
			dda->ny += dda->delta_y;
	}
	return (is_hit);
}

static double	singleray_to_dist(t_view *vu, t_map *map, t_dda *dda)
{
	double	angle_per_pixel;
	double	fovh_2;
	double	ray;

	angle_per_pixel = ft_deg2rad(FOV) / (SX - 1.);
	fovh_2 = ft_deg2rad(FOV) / 2.0;
	ray = (vu->theta + fovh_2) - (angle_per_pixel * (int)(SX / 2));
	if (get_door_intersection(vu, map, dda, ray) == TRUE)
	{
		vu->wl.wall_dist = ft_l2dist(vu->p_x, vu->p_y, \
		vu->wl.wall_x, vu->wl.wall_y);
		vu->wl.wall_dist *= cos(vu->theta - ray);
		return (vu->wl.wall_dist);
	}
	return (-1);
}

void	is_door(t_data *data)
{
	t_dda	dda;
	double	door_dist;

	door_dist = singleray_to_dist(data->vu, data->map, &dda);
	if (0.150000 <= door_dist && door_dist <= 1.4)
	{
		if (data->map->arr[dda.map_x][dda.map_y] == '2')
			data->map->arr[dda.map_x][dda.map_y] = '3';
		else if (data->map->arr[dda.map_x][dda.map_y] == '3')
			data->map->arr[dda.map_x][dda.map_y] = '2';
	}
	render(data);
}
