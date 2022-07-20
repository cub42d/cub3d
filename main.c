/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:11:20 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/21 04:28:10 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include <stdio.h>

static void	init_data(t_data *data)
{
	data->map = ft_calloc(sizeof(t_map));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_error_exit(ARGUMENT_ERROR);
	init_data(&data);
	parse_main(data.map, argv[1]);
}
