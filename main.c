/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:11:20 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 03:32:37 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include "mlx.h"

static int	main_loop(t_data *data)
{
	if (data->vu->flag == 1)
	{
		data->vu->loop -= 1;
		if (data->vu->loop == 0)
			data->vu->flag = 0;
	}
	else
	{
		if (data->vu->loop == 50)
			data->vu->loop = 0;
		data->vu->loop += 1;
	}
	render(data);
	mlx_hook(data->vu->mlx_win, 2, 0, key_down_event, data);
	mlx_hook(data->vu->mlx_win, 6, 0, mouse_move_event, data);
	mlx_hook(data->vu->mlx_win, REDCROSS, 0, clear_all, data);
	return (0);
}

static void	init_data(t_data *data)
{
	data->map = ft_calloc(sizeof(t_map));
	data->vu = ft_calloc(sizeof(t_view));
}

int	clear_all(t_data *data)
{
	mlx_destroy_image(data->vu->mlx, data->vu->img);
	mlx_destroy_image(data->vu->mlx, data->minimap->img);
	mlx_destroy_window(data->vu->mlx, data->vu->mlx_win);
	ft_double_free(&data->map->arr);
	ft_free((void **)&data->vu->sprite);
	ft_free((void **)&data->minimap);
	ft_free((void **)&data->map);
	ft_free((void **)&data->vu);
	ft_free((void **)&data);
	ft_exit("EXIT");
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		ft_error_exit(ARGUMENT_ERROR);
	data = ft_malloc(sizeof(t_data));
	init_data(data);
	parse_main(data->map, argv[1]);
	init_vu(data->vu, data->map);
	init_minimap(data);
	mlx_loop_hook(data->vu->mlx, main_loop, data);
	mlx_loop(data->vu->mlx);
	return (0);
}
