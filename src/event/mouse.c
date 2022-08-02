/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:36:57 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/02 17:23:36 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "utils.h"
#include "mlx.h"

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
