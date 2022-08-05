/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 07:08:27 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/05 09:30:40 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "mlx.h"

void	draw_player(t_data *data)
{
	double	i;
	double	j;

	i = -0.5;
	while (++i < data->map->height * PIXEL_SIZE)
	{
		j = -0.5;
		while (++j < data->map->width * PIXEL_SIZE)
			if (j >= data->vu->p_y - 0.5 && j <= data->vu->p_y + 0.5 && \
					i >= data->vu->p_x - 0.5 && i <= data->vu->p_x + 0.5)
				data->minimap->addr[(int)((i * PIXEL_SIZE * (data->minimap->line_len / 4) + (j * PIXEL_SIZE)))] = 0x0000FF;
	}
}
