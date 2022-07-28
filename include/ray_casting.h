#ifndef RAY_CASTING_H
#define RAY_CASTING_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include <unistd.h>


typedef enum { DIR_N = 0, DIR_E, DIR_W, DIR_S } dir_t;

typedef struct s_dda
{
	/* data */
	int		delta_x;
	int		delta_y;
	double	x_slope;
	double	y_slope;
	double	nx;
	double	ny;
	double	f_x;
	double	g_x;
	int		map_x;
	int		map_y;
	double	dist_horiz;
	double	dist_verti;
	int		hit_side;
}	t_dda;


typedef struct s_tex
{
	char	*img_path;
	void	*img_ptr;
	int		*texture;
	int		px_wid;
	int		px_hei;
	int		tex_bpp;
	int		tex_line_len;
	int		tex_endian;
}	t_tex;

typedef struct s_wall
{
	/* data */
	double	wall_x;
	double	wall_y;
	dir_t	wall_dir;
	double	wall_dist;
}	t_wall;

typedef struct s_view
{
	t_tex	tex_wall[4];
	t_wall	wl;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	double	px;
	double	py;
	double	theta;
	int		ceiling_colour;
	int		floor_colour;
}	t_view;

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

# define	_2PI	6.28318530717958647692
# define	ROT_UNIT	0.03
# define	MOVE_UNIT	0.1

# define W		13
# define S		1
# define A		0
# define D		2
# define ESC	53
# define LEFT	123
# define RIGHT	124


static const double	ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

enum { VERT, HORIZ };

# define FALSE	0
# define TRUE	1


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
