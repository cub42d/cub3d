/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:32:24 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/21 05:39:09 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void	parse_texture(t_map *map, int file)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 6)
	{
		get_next_line(file, &line);

	}
}
