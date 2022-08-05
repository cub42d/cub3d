/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 06:51:05 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/05 09:58:57 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"
#include "utils.h"
#include "mlx.h"

static void	fill_squares(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (int)(PIXEL_SIZE))
	{
		j = -1;
		while (++j < (int)(PIXEL_SIZE))
		{
			data->minimap->addr[((int)(MINI_SCALE * SX) * (y + i)) \
				+ (x + j)] = color;
		}
	}
}

void	render_map(t_data *data)
{
	int					col;
	int					row;

	row = -1;
	while (++row < data->map->height)
	{
		col = -1;
		if (row > (int)(MINI_SCALE * SY / (int)(PIXEL_SIZE)))
			break ;
		while (++col < data->map->width)
		{
			if (col < (int)(MINI_SCALE * SX / (int)(PIXEL_SIZE)))
			{
				if (data->map->arr[row][col] == '1')
					fill_squares(data, ((int)(PIXEL_SIZE) * col), \
					((int)(PIXEL_SIZE) * row), 0x345433);
				else if (data->map->arr[row][col] == '0')
					fill_squares(data, ((int)(PIXEL_SIZE) * col), \
					((int)(PIXEL_SIZE) * row), 0xffffff);
			}
		}
	}
	mlx_put_image_to_window(data->vu->mlx, data->vu->mlx_win, \
	data->minimap->img, 0, 0);
}
