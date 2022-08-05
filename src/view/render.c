/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:58:52 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/05 09:40:48 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "utils.h"
#include <math.h>

static void	put_vertical_solid_color_line(t_view *vu, \
											int x, int color, int point)
{
	char	*dst;
	int		y_start;
	int		y_end;

	if (point == 1)
	{
		y_start = 0;
		y_end = SY / 2;
	}
	else
	{
		y_start = SY / 2;
		y_end = SY;
	}
	while (y_start < y_end)
	{
		dst = vu->addr + (y_start * vu->line_len + x * (vu->bpp / 8));
		*(unsigned int *)dst = color;
		y_start++;
	}
}

static void	clear_screen(t_view *vu, t_map *map)
{
	int	x;

	x = 0;
	while (x < SX)
	{
		put_vertical_solid_color_line(vu, x, map->c, 1);
		put_vertical_solid_color_line(vu, x, map->f, 0);
		x++;
	}
}

static int	get_wall_intersection(t_view *vu, t_map *map, double ray)
{
	t_dda	dda;
	int		cell;
	int		is_hit;

	init_dda(vu, &dda, ray);
	is_hit = FALSE;
	while (!is_hit)
	{
		get_map_x_y(vu, &dda);
		cell = map_get_cell(map, dda.map_x, dda.map_y);
		if (cell < 0)
			break ;
		if (cell == 1)
		{
			get_ray_wall_var(vu, &dda);
			is_hit = TRUE;
			break ;
		}
		if (dda.hit_side == VERT)
			dda.nx += dda.delta_x;
		else
			dda.ny += dda.delta_y;
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
	return (vu->wl.wall_dist);
}

void	render(t_data *data)
{
	int	x;

	mlx_do_sync(data->vu->mlx);
	clear_screen(data->vu, data->map);
	x = -1;
	while (++x < SX)
	{
		data->vu->wl.wall_dist = cast_single_ray(data->vu, data->map, \
													x, data->vu->theta);
		draw_textured_wall(data->vu, x, data->vu->wl.wall_dist);
	}
	mlx_put_image_to_window(data->vu->mlx, data->vu->mlx_win, \
							data->vu->img, 0, 0);
	render_map(data);
	//draw_player(data);
	mlx_do_sync(data->vu->mlx);
}
