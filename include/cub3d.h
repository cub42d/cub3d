/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:13:19 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/08 16:02:37 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parser.h"
# include "macro.h"

typedef struct s_data		t_data;
typedef struct s_dda		t_dda;
typedef struct s_tex		t_tex;
typedef struct s_wall		t_wall;
typedef struct s_view		t_view;
typedef struct s_draw_wall	t_draw_wall;
typedef struct s_minimap	t_minimap;

struct s_data
{
	t_view		*vu;
	t_map		*map;
	t_minimap	*minimap;
};

struct s_minimap
{
	void		*img;
	int			*addr;
	int			bpp;
	int			line_len;
	int			endian;
};

struct s_dda
{
	int			delta_x;
	int			delta_y;
	double		x_slope;
	double		y_slope;
	double		nx;
	double		ny;
	double		f_x;
	double		g_x;
	int			map_x;
	int			map_y;
	double		dist_horiz;
	double		dist_verti;
	int			hit_side;
};

struct s_tex
{
	char		*img_path;
	void		*img_ptr;
	int			*texture;
	int			px_wid;
	int			px_hei;
	int			tex_bpp;
	int			tex_line_len;
	int			tex_endian;
};

struct s_wall
{
	double		wall_x;
	double		wall_y;
	t_dir		wall_dir;
	double		wall_dist;
};

struct s_draw_wall
{
	double		texture_ratio;
	int			tx;
	int			ty;
	int			wall_height;
	int			y0;
	int			y1;
	int			y_start;
	int			y_end;
	int			color;
};

struct s_view
{
	t_tex		tex_wall[5];
	t_wall		wl;
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	double		p_x;
	double		p_y;
	double		theta;
	int			is_door;
};

//		event
//			key_down.c
int				key_down_event(int keycode, t_data *data);
//			mouse.c
int				mouse_move_event(int x, int y, t_data *data);
//			move_utils.c
void			rotate_player(t_data *data, double delta);
int				move_player(t_data *data, int keycode);

//		view
//			init.c
void			init_vu(t_view *vu, t_map *map);
//			draw.c
void			draw_textured_wall(t_view *vu, int x, double wall_dist);
//			raycast_util.c
int				map_get_cell(t_map *map, int x, int y);
void			get_map_x_y(t_view *vu, t_dda *dda);
void			get_ray_wall_var(t_view *vu, t_dda *dda);
void			init_dda(t_view *vu, t_dda *dda, double ray);
//			render.c
void			render(t_data *data);
//			raycast.c
double			cast_single_ray(t_view *vu, t_map *map, int x, double theta);

//			main.c
int				clear_all(t_data *data);

//		minimap
//			init_minimap.c
void			init_minimap(t_data *data);
//			draw_minimap.c
void			render_map(t_data *data);
//			draw_player.c
void			draw_player(t_data *data);

//		door
//			door_evnet.c
void			is_door(t_data *data);

#endif
