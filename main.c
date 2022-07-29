/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:11:20 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/30 05:30:13 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include "mlx.h"

static void	init_data(t_data *data)
{
	data->map = ft_calloc(sizeof(t_map));
	data->vu = ft_calloc(sizeof(t_view));
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
	render(data);
	mlx_hook(data->vu->mlx_win, 2, 0, key_down_event, &data->vu);
	mlx_hook(data->vu->mlx_win, 6, 0, mouse_move_event, &data->vu);
	mlx_loop(data->vu->mlx);
	return (0);
}
