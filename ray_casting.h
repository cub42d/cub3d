#ifndef RAY_CASTING_H
#define RAY_CASTING_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_data;


# define	EPS	(1e-06)
# define	is_zero(d)	(fabs(d) < EPS)
# define	deg2rad(d)	((d) * M_PI / 180.0)
# define	rad2dig(d)	((d) * 180.0 / M_PI)
# define	min(a, b)	((a) < (b) ? (a) : (b))
# define	max(a, b)	((a) > (b) ? (a) : (b))

# define	SX		1080
# define	SY		1000
# define	FOV		60
# define	FOV_H	deg2rad(FOV)
# define	FOV_V	(FOV_H * ((double)SY / (double)SX))
# define	WALL_H	1.0

// # define	_2PI	6.28318530717958647692
// # define	ROT_UNIT	0.03
// # define	MOVE_UNIT	0.1

// # define W		13
// # define S		1
// # define A		2
// # define D		0
// # define ESC	53
// # define LEFT	123
// # define RIGHT	124

// typedef struct
// {
// 	double	x;
// 	double	y;
// 	double	theta;
// }	coord_t;

// typedef struct s_info
// {

// }	t_info;


static const double	ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

enum { VERT, HORIZ };

# define FALSE	0
# define TRUE	1

typedef enum { DIR_N = 0, DIR_E, DIR_W, DIR_S } dir_t;

# define MAPX 6
# define MAPY 5

static int	map[MAPX][MAPY] =
{
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 0, 0, 1},
	{1, 1, 0, 0, 1},
	{1, 1, 1, 1, 1}
};

#endif
