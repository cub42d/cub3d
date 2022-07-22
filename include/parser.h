/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:32:26 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/22 07:19:28 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map		t_map;

struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	char	**arr;
	int		width;
	int		height;
};

void	parse_main(t_map *map, char *argv);
void	parse_texture(t_map *map, int file);
void	parse_map(t_map *map, int file);

#endif
