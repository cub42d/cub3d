/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 07:08:27 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 20:19:38 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "mlx.h"

static void	set_player_color(t_data *data, double x, double y, int line)
{
	if (y < SX / 2 && x / (SX / 2) < SY / 2)
	{
		data->minimap->addr[(int)(x + y)] = 0x00030D;
		data->minimap->addr[(int)(x + y + 1)] = 0x00030D;
		data->minimap->addr[(int)(x + y - 1)] = 0x00030D;
		data->minimap->addr[(int)(x + y + 2)] = 0x00030D;
		data->minimap->addr[(int)(x + y - 2)] = 0x00030D;
		data->minimap->addr[(int)((x - ((line / 4))) + y)] = 0x00030D;
		data->minimap->addr[(int)((x - ((line / 4))) + y + 1)] = 0x00030D;
		data->minimap->addr[(int)((x - ((line / 4))) + y - 1)] = 0x00030D;
		data->minimap->addr[(int)((x + ((line / 4))) + y)] = 0x00030D;
		data->minimap->addr[(int)((x + ((line / 4))) + y + 1)] = 0x00030D;
		data->minimap->addr[(int)((x + ((line / 4))) + y - 1)] = 0x00030D;
		data->minimap->addr[(int)((x - ((line / 2))) + y)] = 0x00030D;
		data->minimap->addr[(int)((x + ((line / 2))) + y)] = 0x00030D;
	}
}

void	draw_player(t_data *data)
{
	double	i;
	double	j;

	i = -0.5;
	while (++i < data->map->height * PIXEL_SIZE)
	{
		j = -0.5;
		while (++j < data->map->width * PIXEL_SIZE)
		{
			if (j >= data->vu->p_y - 0.5 && j <= data->vu->p_y + 0.5 && \
			i >= data->vu->p_x - 0.5 && i <= data->vu->p_x + 0.5)
			{
				set_player_color(data, i * PIXEL_SIZE * \
				(data->minimap->line_len / 4), \
				j * PIXEL_SIZE, data->minimap->line_len);
			}
		}
	}
}
