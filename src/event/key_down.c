/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:48:11 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/02 17:32:33 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include "macro.h"

int	key_down_event(int keycode, t_data *data)
{
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		move_player(data, keycode);
	else if (keycode == LEFT || keycode == RIGHT)
	{
		if (keycode == LEFT)
			rotate_player(data, ROT_UNIT * 1.2);
		else
			rotate_player(data, ROT_UNIT * (-1.2));
	}
	else if (keycode == ESC)
		ft_exit("EXIT");
	return (0);
}
