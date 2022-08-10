/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:25:04 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 20:18:43 by hmoon            ###   ########.fr       */
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
# define MOVE_UNIT			0.2
# define EPS				(1e-06)

# define W					13
# define S					1
# define A					0
# define D					2
# define E					14
# define REDCROSS			17
# define ESC				53
# define LEFT				123
# define RIGHT				124

# define FALSE				0
# define TRUE				1

# define MINI_SCALE			0.5
# define TILE_SIZE			20
# define PIXEL_SIZE			10

# define DOOR_XPM			"./texture/door.xpm"
# define SPRITE_XPM1		"./texture/sprite/sprite1.xpm"
# define SPRITE_XPM2		"./texture/sprite/sprite2.xpm"
# define SPRITE_XPM3		"./texture/sprite/sprite3.xpm"
# define SPRITE_XPM4		"./texture/sprite/sprite4.xpm"
# define SPRITE_XPM5		"./texture/sprite/sprite5.xpm"
# define SPRITE_XPM6		"./texture/sprite/sprite6.xpm"
# define SPRITE_XPM7		"./texture/sprite/sprite7.xpm"
# define SPRITE_XPM8		"./texture/sprite/sprite8.xpm"
# define SPRITE_XPM9		"./texture/sprite/sprite9.xpm"
# define SPRITE_XPM10		"./texture/sprite/sprite10.xpm"

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
	DIR_S,
	DOOR,
	SPRITE1,
	SPRITE2,
	SPRITE3,
	SPRITE4,
	SPRITE5,
	SPRITE6,
	SPRITE7,
	SPRITE8,
	SPRITE9,
	SPRITE10
};

enum e_hit
{
	VERT,
	HORIZ
};

#endif
