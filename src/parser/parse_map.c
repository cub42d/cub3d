/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 07:15:17 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/22 07:37:38 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "macro.h"
#include "utils.h"

static void	get_map_size(t_map *map, int file)
{
	char	*temp;

	while (get_next_line(file, temp))
	{

	}
}

void	parse_map(t_map *map, int file)
{
	get_map_size(map, file);
}
