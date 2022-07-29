/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 23:28:29 by hmoon             #+#    #+#             */
/*   Updated: 2022/07/30 04:38:30 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vu.h"
#include "macro.h"
#include "utils.h"

static void	get_player_position(t_view *vu, t_map *map)
{
	if (map->p_pos == POS_W)
		vu->theta = ft_deg2rad(0);
	if (map->p_pos == POS_E)
		vu->theta = ft_deg2rad(60);
	if (map->p_pos == POS_N)
		vu->theta = ft_deg2rad(90);
	if (map->p_pos == POS_S)
		vu->theta = ft_deg2rad(120);
}

static void	define_wall_texture(t_view *vu, char *img_dir, t_dir dir)
{
	vu->tex_wall[dir].img_path = img_dir;
	vu->tex_wall[dir].px_wid = 64;
	vu->tex_wall[dir].px_hei = 64;
	vu->tex_wall[dir].img_ptr = mlx_xpm_file_to_image(vu->mlx, \
	vu->tex_wall[dir].img_path, &vu->tex_wall[dir].px_wid, \
	&vu->tex_wall[dir].px_hei);
	vu->tex_wall[dir].texture = (int *)(mlx_get_data_addr(\
	vu->tex_wall[dir].img_ptr, &vu->tex_wall[dir].tex_bpp, \
	&vu->tex_wall[dir].tex_line_len, &vu->tex_wall[dir].tex_endian));
}

void	init_vu(t_view *vu, t_map *map)
{
	vu->p_x = map->p_y;
	vu->p_y = map->p_x;
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
	define_wall_texture(&vu, map->no, DIR_N);
	define_wall_texture(&vu, map->ea, DIR_E);
	define_wall_texture(&vu, map->we, DIR_W);
	define_wall_texture(&vu, map->so, DIR_S);
}