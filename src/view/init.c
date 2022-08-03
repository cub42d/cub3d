/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 23:28:29 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/03 20:36:34 by hyunkkim         ###   ########seoul.kr  */
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

static void	define_texture(t_view *vu, char *img_dir, t_dir dir)
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
	//static const	*door_file = "./texture/door.xpm";
	//static const	*sprite1_file = "./texture/sprite1.xpm";
	//static const	*sprite2_file = "./texture/sprite2.xpm";

	define_texture(vu, map->no, DIR_N);
	define_texture(vu, map->ea, DIR_E);
	define_texture(vu, map->we, DIR_W);
	define_texture(vu, map->so, DIR_S);
	//define_texture(vu, door_file, DOOR);
	//define_texture(vu, sprite1_file, SPRITE_1);
	//define_texture(vu, sprite2_file, SPRITE_2);
}

static void	init_visible(t_view *vu, t_map *map)
{
	int	i;
	int	j;

	vu->visible = ft_calloc(sizeof(int *) * (map->height));
	i = 0;
	while (i < map->height)
	{
		vu->visible[i] = ft_calloc(sizeof(int) * (map->width));
		while (j < map->width)
		{
			vu->visible[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	init_vu(t_view *vu, t_map *map)
{
	vu->p_x = map->p_y + 0.5;
	vu->p_y = map->p_x + 0.5;
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
	init_visible(vu, map);
}
