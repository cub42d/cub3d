/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:18:01 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 02:24:10 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "utils.h"
#include "mlx.h"

void	init_minimap(t_data *data)
{
	int	y;
	int	x;

	data->minimap = ft_malloc(sizeof(t_minimap));
	data->minimap->img = mlx_new_image(data->vu->mlx, \
		(int)(SX * MINI_SCALE), (int)(SY * MINI_SCALE));
	data->minimap->addr = (int *)mlx_get_data_addr(data->minimap->img, \
		&data->minimap->bpp, &data->minimap->line_len, &data->minimap->endian);
	y = -1;
	while (++y < (int)(SY * MINI_SCALE))
	{
		x = -1;
		while (++x < (int)(SX * MINI_SCALE))
			data->minimap->addr[(y * (int)(SX * MINI_SCALE)) + x] = 0xffffff00;
	}
}
