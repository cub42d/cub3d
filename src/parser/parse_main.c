/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:50:59 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/29 15:30:30 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "macro.h"
#include "utils.h"

void	parse_main(t_map *map, char *argv)
{
	int	file;

	if ((!ft_iseq(argv + ft_strlen(argv) - 4, ".cub")) || ft_strlen(argv) < 5)
		ft_error_exit(FILE_ERROR);
	file = ft_open(argv, 0x0000);
	parse_texture(map, file);
	parse_map(map, file);
	ft_close(file);
}
