/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:42:59 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 02:52:38 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include "macro.h"
#include <math.h>

static void	colision_calibration(t_map *map, double *x, double *y)
{
	double	t;
	double	e;
	double	m;
	double	p;

	if ((map_get_cell(map, (int)floor(*x) - 1, (int)*y) != 0) \
		&& (modf(*x, &t) <= 0.2))
		*x = t + 0.2;
	if ((map_get_cell(map, (int)ceil(*x), (int)*y) != 0) \
		&& (modf(*x, &e) >= 0.8))
		*x = e + 0.8;
	if ((map_get_cell(map, (int)*x, (int)floor(*y) - 1) != 0)
		&& (modf(*y, &m) <= 0.2))
		*y = m + 0.2;
	if ((map_get_cell(map, (int)*x, (int)ceil(*y)) != 0) \
		&& (modf(*y, &p) >= 0.8))
		*y = p + 0.8;
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

int	move_player(t_data *data, int keycode)
{
	double	delta_x;
	double	delta_y;
	double	new_x;
	double	new_y;

	if (get_offset(data->vu->theta, keycode, &delta_x, &delta_y))
		return (ft_print_err("invalid key press"));
	new_x = data->vu->p_x + delta_x;
	new_y = data->vu->p_y + delta_y;
	if (map_get_cell(data->map, new_x, new_y) == 1 \
	|| map_get_cell(data->map, new_x, new_y) == 2)
		return (ft_print_err("bump"));
	colision_calibration(data->map, &new_x, &new_y);
	data->vu->p_x = new_x;
	data->vu->p_y = new_y;
	render(data);
	return (0);
}

void	rotate_player(t_data *data, double delta)
{
	data->vu->theta += delta;
	if (data->vu->theta < 0)
		data->vu->theta += _2PI;
	else if (data->vu->theta > _2PI)
		data->vu->theta -= _2PI;
	render(data);
}
