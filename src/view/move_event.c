/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:40:22 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/02 02:25:07 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static void	colision_calibration(t_map *map, double *x, double *y)
{
	double	t;
	double	e;
	double	m;
	double	p;

	if ((map_get_cell(map, (int)floor(*x) - 1, (int)*y) != 0) \
		&& (modf(*x, &t) <= 0.1))
		*x = t + 0.1;
	if ((map_get_cell(map, (int)ceil(*x), (int)*y) != 0) \
		&& (modf(*x, &e) >= 0.9))
		*x = e + 0.9;
	if ((map_get_cell(map, (int)*x, (int)floor(*y) - 1) != 0)
		&& (modf(*y, &m) <= 0.1))
		*y = m + 0.1;
	if ((map_get_cell(map, (int)*x, (int)ceil(*y)) != 0) \
		&& (modf(*y, &p) >= 0.9))
		*y = p + 0.9;
}

static int	get_offset(double theta, int keycode, \
							double *delta_x, double *delta_y)
{
	if (keycode == W)
	{
		*delta_x = 1 * MOVE_UNIT * cos(theta);
		*delta_y = 1 * MOVE_UNIT * sin(theta);
	}
	else if (keycode == A)
	{
		*delta_x = MOVE_UNIT * cos(theta + (1 * M_PI_2));
		*delta_y = MOVE_UNIT * sin(theta + (1 * M_PI_2));
	}
	else if (keycode == S)
	{
		*delta_x = -1 * MOVE_UNIT * cos(theta);
		*delta_y = -1 * MOVE_UNIT * sin(theta);
	}
	else if (keycode == D)
	{
		*delta_x = MOVE_UNIT * cos(theta + (-1 * M_PI_2));
		*delta_y = MOVE_UNIT * sin(theta + (-1 * M_PI_2));
	}
	else
		return (1);
	return (0);
}

static int	move_player(t_data *data, int keycode)
{
	double	delta_x;
	double	delta_y;
	double	new_x;
	double	new_y;

	if (get_offset(data->vu->theta, keycode, &delta_x, &delta_y))
		return (ft_print_err("invalid key press"));
	new_x = data->vu->p_x + delta_x;
	new_y = data->vu->p_y + delta_y;
	if (map_get_cell(data->map, new_x, new_y) != 0)
		return (ft_print_err("bump"));
	colision_calibration(data->map, &new_x, &new_y);
	data->vu->p_x = new_x;
	data->vu->p_y = new_y;
	render(data);
	return (0);
}

static void	rotate_player(t_data *data, double delta)
{
	data->vu->theta += delta;
	if (data->vu->theta < 0)
		data->vu->theta += _2PI;
	else if (data->vu->theta > _2PI)
		data->vu->theta -= _2PI;
	render(data);
}

int	key_down_event(int keycode, t_data *data)
{
	if (keycode == W || keycode == A || keycode == S || keycode == D)
	{
		move_player(data, keycode);
	}
	else if (keycode == LEFT || keycode == RIGHT)
	{
		if (keycode == LEFT)
			rotate_player(data, ROT_UNIT * 1.2);
		else
			rotate_player(data, ROT_UNIT * (-1.2));
	}
	else if (keycode == ESC)
	{
		printf("Exit\n");
		exit(0);
	}
	return (0);
}

int	mouse_move_event(int x, int y, t_data *data)
{
	static int	prev_x = 0;
	static int	prev_y = 0;
	double		dist;

	mlx_do_sync(data->vu->mlx);
	if ((0 > prev_x && prev_x > SX) || (0 > prev_x && prev_x > SX))
	{
		prev_x = 0;
		prev_y = 0;
	}
	mlx_mouse_get_pos(data->vu->mlx_win, &x, &y);
	dist = ft_l2dist(prev_x, prev_y, x, y);
	if ((0 < x && x < SX) && (0 < y && y < SY))
	{
		if ((x - prev_x) < 0)
			rotate_player(data, ROT_UNIT * (dist * 0.3));
		else if ((x - prev_x) > 0)
			rotate_player(data, ROT_UNIT * (dist * -0.3));
	}
	prev_x = x;
	prev_y = y;
	mlx_do_sync(data->vu->mlx);
	return (0);
}
