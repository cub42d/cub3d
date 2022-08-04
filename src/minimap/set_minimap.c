/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:18:01 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/05 04:56:33 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "utils.h"
#include "mlx.h"

static void fill_squares(t_data *data, int x, int y, int color)
{
	int i;
	int j;

	j = 0;
	while (j < (int)(MINI_SCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINI_SCALE * TILE_SIZE))
		{
			data->minimap->addr[(int)(MINI_SCALE * SX) * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	render_map(t_data *data)
{
	int col;
	int row;

	row = -1;
	while (++row < data->map->height)
	{
		col = -1;
		if (row > (int)(MINI_SCALE * SY / (TILE_SIZE * MINI_SCALE)))
			break ;
		while (++col < data->map->width)
		{
			if (col < (int)(MINI_SCALE * SX / (TILE_SIZE * MINI_SCALE)))
			{
				if (data->map->arr[row][col] == '1')
					fill_squares(data, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), 0x345433);
				else if (data->map->arr[row][col] == '0')
					fill_squares(data, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), 0xffffff);
			}
		}
	}
	mlx_put_image_to_window(data->vu->mlx, data->vu->mlx_win, data->minimap->img, 0, 0);
}

void	init_minimap(t_data *data)
{
	int	y;
	int	x;

	data->minimap = ft_malloc(sizeof(t_minimap));
	data->minimap->img = mlx_new_image(data->vu->mlx, (int)(SX * MINI_SCALE), (int)(SY * MINI_SCALE));
	data->minimap->addr = (int *)mlx_get_data_addr(data->minimap->img, &data->minimap->bpp, &data->minimap->line_len, &data->minimap->endian);
	y = -1;
	while (++y < (int)(SY * MINI_SCALE))
	{
		x = -1;
		while (++x < (int)(SX * MINI_SCALE))
			data->minimap->addr[(y * (int)(SX * MINI_SCALE)) + x] = 0xffffff00;
	}
}
