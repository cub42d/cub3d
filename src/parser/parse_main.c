/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:50:59 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/21 04:32:59 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"

void	parse_main(t_map *map, char *argv)
{
	int	file;

	if ((!ft_iseq(argv + ft_strlen(argv) - 4, ".cub")) || ft_strlen(argv) < 5)
		ft_error_exit(FILE_ERROR);
	file = ft_open(argv, 0x0000);
	parse_texture(map, file);
}
