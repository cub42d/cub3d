/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:25:04 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/31 09:40:20 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# define ARGUMENT_ERROR		"Error: Invalid argument"
# define FILE_ERROR			"Error: Invaild file name"
# define MAP_ERROR			"Error: Invaild map file"
# define MLX_ERROR			"Error: mlx function error"

# define NORTH				"NO"
# define SOUTH				"SO"
# define WEST				"WE"
# define EAST				"EA"
# define FLOOR				"F"
# define CELLING			"C"

# define TITLE				"cub3D"
# define SX					1280
# define SY					960
# define FOV				60
# define WALL_H				1.0

# define _2PI				6.28318530717958647692
# define ROT_UNIT			0.02
# define MOVE_UNIT			0.1
# define EPS				(1e-06)

# define W					13
# define S					1
# define A					0
# define D					2
# define ESC				53
# define LEFT				123
# define RIGHT				124

# define FALSE				0
# define TRUE				1

typedef enum e_dir			t_dir;

enum e_pos
{
	POS_N = 1 << 1,
	POS_W = 1 << 2,
	POS_S = 1 << 3,
	POS_E = 1 << 4,
};

enum e_dir
{
	DIR_N = 0,
	DIR_E,
	DIR_W,
	DIR_S
};

enum e_hit
{
	VERT,
	HORIZ
};

#endif
