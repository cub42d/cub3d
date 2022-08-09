/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 23:28:29 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/10 03:41:24 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "utils.h"

static void	get_player_position(t_view *vu, t_map *map)
{
	if (map->p_pos == POS_W)
		vu->theta = ft_deg2rad(0);
	if (map->p_pos == POS_S)
		vu->theta = ft_deg2rad(90);
	if (map->p_pos == POS_E)
		vu->theta = ft_deg2rad(180);
	if (map->p_pos == POS_N)
		vu->theta = ft_deg2rad(270);
}

void	define_texture(t_view *vu, char *img_dir, t_dir dir)
{
	vu->tex_wall[dir].img_path = img_dir;
	vu->tex_wall[dir].img_ptr = mlx_xpm_file_to_image(vu->mlx, \
	vu->tex_wall[dir].img_path, &vu->tex_wall[dir].px_wid, \
	&vu->tex_wall[dir].px_hei);
	if (vu->tex_wall[dir].img_ptr == NULL)
		ft_error_exit(MLX_ERROR);
	if (vu->tex_wall[dir].px_wid != 64 || vu->tex_wall[dir].px_hei != 64)
		ft_error_exit("Error: texture pixel not 64");
	vu->tex_wall[dir].texture = (int *)(mlx_get_data_addr(\
	vu->tex_wall[dir].img_ptr, &vu->tex_wall[dir].tex_bpp, \
	&vu->tex_wall[dir].tex_line_len, &vu->tex_wall[dir].tex_endian));
}

static void	init_texture(t_view *vu, t_map *map)
{
	define_texture(vu, map->no, DIR_N);
	define_texture(vu, map->ea, DIR_E);
	define_texture(vu, map->we, DIR_W);
	define_texture(vu, map->so, DIR_S);
	define_texture(vu, DOOR_XPM, DOOR);
	define_texture(vu, SPRITE_XPM1, SPRITE1);
	define_texture(vu, SPRITE_XPM2, SPRITE2);
	define_texture(vu, SPRITE_XPM3, SPRITE3);
	define_texture(vu, SPRITE_XPM4, SPRITE4);
	define_texture(vu, SPRITE_XPM5, SPRITE5);
	define_texture(vu, SPRITE_XPM6, SPRITE6);
	define_texture(vu, SPRITE_XPM7, SPRITE7);
	define_texture(vu, SPRITE_XPM8, SPRITE8);
	define_texture(vu, SPRITE_XPM9, SPRITE9);
	define_texture(vu, SPRITE_XPM10, SPRITE10);
}

void	init_vu(t_view *vu, t_map *map)
{
	vu->p_x = map->p_y + 0.5;
	vu->p_y = map->p_x + 0.5;
	vu->fovh_2 = ft_deg2rad(FOV) / 2.0;
	get_player_position(vu, map);
	vu->mlx = mlx_init();
	if (!vu->mlx)
		ft_error_exit(MLX_ERROR);
	vu->mlx_win = mlx_new_window(vu->mlx, SX, SY, TITLE);
	if (!vu->mlx_win)
		ft_error_exit(MLX_ERROR);
	vu->img = mlx_new_image(vu->mlx, SX, SY);
	if (!vu->img)
		ft_error_exit(MLX_ERROR);
	vu->addr = mlx_get_data_addr(vu->img, &vu->bpp, \
		&vu->line_len, &vu->endian);
	if (!vu->addr || vu->bpp != 32 || vu->endian != 0)
		ft_error_exit(MLX_ERROR);
	init_texture(vu, map);
	if (map->sprite_cnt > 0)
		vu->sprite = ft_calloc(sizeof(t_sprite) * map->sprite_cnt);
}
