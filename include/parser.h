/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:32:26 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/09 19:21:07 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_map		t_map;
typedef struct s_parse		t_parse;

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
	double	p_x;
	double	p_y;
	int		p_pos;
	int		sprite_cnt;
};

struct s_parse
{
	char	**prv;
	char	**arr;
	char	*str;
	int		width;
	int		size;
	int		x;
	int		y;
};

void	parse_main(t_map *map, char *argv);
void	parse_texture(t_map *map, int file);
void	parse_map(t_map *map, int file);

#endif
