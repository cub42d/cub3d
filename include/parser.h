/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:32:26 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/21 04:47:17 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map		t_map;

struct s_map
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		f;
	int		c;
	char	**arr;
	int		width;
	int		height;
};

void	parse_main(t_map *map, char *argv);
void	parse_texture(t_map *map, int file);

#endif
