/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 01:05:37 by hmoon             #+#    #+#             */
/*   Updated: 2022/08/09 21:33:12 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"
#include <math.h>

void	put_pixel(t_view *vu, int x, int y, int color)
{
	char	*dst;

	dst = vu->addr + (y * vu->line_len + x * (vu->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_wall_height(double dist)
{
	double	fov_h;

	fov_h = 2.0 * dist * tan(ft_fov_v(FOV) / 2.0);
	return ((int)(SY * (WALL_H / fov_h)));
}

int	get_wall_texture(t_tex *tex, int tx, int ty)
{
	int	ret;

	ret = tex->texture[(tex->px_wid * ty) + tx];
	return (ret);
}

static t_tex	*assist_draw(t_view *vu, t_draw_wall *temp, double wall_dist)
{
	t_tex	*texture_temp;

	if (vu->wl.wall_dir == DIR_W || vu->wl.wall_dir == DIR_E)
		temp->texture_ratio = vu->wl.wall_y - floor(vu->wl.wall_y);
	else
		temp->texture_ratio = vu->wl.wall_x - floor(vu->wl.wall_x);
	texture_temp = &vu->tex_wall[vu->wl.wall_dir];
	if (vu->is_door == TRUE)
		texture_temp = &vu->tex_wall[DOOR];
	temp->tx = (int)(temp->texture_ratio * texture_temp->px_wid);
	temp->wall_height = get_wall_height(wall_dist);
	temp->y0 = (int)((SY - temp->wall_height) / 2.0);
	temp->y1 = temp->y0 + temp->wall_height - 1;
	temp->y_start = ft_max(0, temp->y0);
	temp->y_end = ft_min(SY - 1, temp->y1);
	return (texture_temp);
}

void	draw_textured_wall(t_view *vu, int x, double wall_dist)
{
	t_tex		*wall_texture;
	t_draw_wall	*temp;

	temp = ft_calloc(sizeof(t_draw_wall));
	wall_texture = assist_draw(vu, temp, wall_dist);
	while (temp->y_start <= temp->y_end)
	{
		temp->ty = (int)((double)(temp->y_start - temp->y0) * \
		wall_texture->px_hei / temp->wall_height);
		temp->color = get_wall_texture(wall_texture, temp->tx, temp->ty);
		put_pixel(vu, x, temp->y_start, temp->color);
		temp->y_start++;
	}
	ft_free((void **)&temp);
}
