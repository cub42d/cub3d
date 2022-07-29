/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vu.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:32:46 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/30 05:10:58 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VU_H
# define VU_H

# include "parser.h"
# include "macro.h"
# include <math.h>

typedef struct s_dda		t_dda;
typedef struct s_tex		t_tex;
typedef struct s_wall		t_wall;
typedef struct s_view		t_view;
typedef struct s_draw_wall	t_draw_wall;

struct s_dda
{
	int				delta_x;
	int				delta_y;
	double			x_slope;
	double			y_slope;
	double			nx;
	double			ny;
	double			f_x;
	double			g_x;
	int				map_x;
	int				map_y;
	double			dist_horiz;
	double			dist_verti;
	int				hit_side;
};

struct s_tex
{
	char			*img_path;
	void			*img_ptr;
	int				*texture;
	int				px_wid;
	int				px_hei;
	int				tex_bpp;
	int				tex_line_len;
	int				tex_endian;
};

struct s_wall
{
	double			wall_x;
	double			wall_y;
	t_dir			wall_dir;
	double			wall_dist;
};

struct s_draw_wall
{
	double			texture_ratio;
	int				tx;
	int				ty;
	int				wall_height;
	int				y0;
	int				y1;
	int				y_start;
	int				y_end;
	int				color;
};

struct s_view
{
	t_tex			tex_wall[4];
	t_wall			wl;
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	double			p_x;
	double			p_y;
	double			theta;
};

void			init_vu(t_view *vu, t_map *map);
void			draw_textured_wall(t_view *vu, int x, double wall_dist);
int				map_get_cell(t_map *map, int x, int y);
void			get_map_x_y(t_view *vu, t_dda *dda);
void			get_ray_wall_var(t_view *vu, t_dda *dda);
void			init_dda(t_view *vu, t_dda *dda, double ray);
double			cast_single_ray(t_view *vu, t_map *map, int x, double theta);

#endif
