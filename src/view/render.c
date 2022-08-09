/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:58:52 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 02:55:22 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "utils.h"

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
	draw_sprite(data->vu, data->map);
	mlx_put_image_to_window(data->vu->mlx, data->vu->mlx_win, \
							data->vu->img, 0, 0);
	render_map(data);
	mlx_do_sync(data->vu->mlx);
}
