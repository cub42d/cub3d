#include "ray_casting.h"

int	map_get_cell(int x, int y)
{
	if (x >= 0 && x < MAPX && y >= 0  && y < MAPY)
		return (map[x][y]);
	else
		return (-1);
}

int	num_sign(double d)
{
	if (is_zero(d))
		return (0);
	else if (d > 0)
		return (1);
	else
		return (-1);
}

double	l2dist(double x0, double y0, double x1, double y1)
{
	double	dx;
	double	dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}

int	print_err(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	get_wall_intersection \
(double ray, double px, double py, \
dir_t *wall_dir, double *wall_x, double *wall_y)
{
	int	delta_x;
	int	delta_y;
	double	x_slope;
	double	y_slope;
	double	nx;
	double	ny;
	double	f;
	double	g;
	int		is_hit;
	int		hit_side;
	int		mapx;
	int		mapy;
	double	dist_verti;
	double	dist_horiz;
	int		cell;

	delta_x = num_sign(cos(ray));
	delta_y = num_sign(sin(ray));
	if (delta_x == 0)
		x_slope = INFINITY;
	else
		x_slope = tan(ray);
	if (delta_y == 0)
		y_slope = INFINITY;
	else
		y_slope = 1./tan(ray);
	if (delta_x > 0)
		nx = floor(px) + 1;
	else
	{
		if (delta_x < 0)
			nx = ceil(px) - 1;
		else
			nx = px;
	}
	if (delta_y > 0)
		ny = floor(py) + 1;
	else
	{
		if (delta_y < 0)
			ny = ceil(py) - 1;
		else
			ny = py;
	}
	// printf("\nray=%.2f def, delta_x=%d, delta_y=%d, x_slope=%.2f, y_slope=%.2f, nx=%.2f, ny=%.2f", rad2dig(ray), delta_x, delta_y, x_slope, y_slope, nx, ny);
	f = INFINITY;
	g = INFINITY;
	is_hit = FALSE;
	while (!is_hit)
	{
		if (delta_x != 0)
			f = x_slope * (nx - px) + py;
		if (delta_y != 0)
			g = y_slope * (ny - py) + px;
		dist_verti = l2dist(px, py, nx, f);
		dist_horiz = l2dist(px, py, g, ny);
		if (dist_verti < dist_horiz)
		{
			if (delta_x == 1)
				mapx = (int)nx;
			else
				mapx = (int)nx - 1;
			mapy = (int)f;
			hit_side = VERT;
			// printf("V(%d, %.2f) -> ", mapx, f);
		}
		else
		{
			mapx = (int)g;
			if (delta_y == 1)
				mapy = (int)ny;
			else
				mapy = (int)ny - 1;
			hit_side = HORIZ;
			// printf("H(%.2f, %d) -> ", g, mapy);
		}
		cell = map_get_cell(mapx, mapy);
		if (cell < 0)
			break ;
		if (cell == 1)
		{
			if (hit_side == VERT)
			{
				if (delta_x > 0)
					*wall_dir = DIR_W;
				else
					*wall_dir = DIR_E;
				*wall_x = nx;
				*wall_y = f;
			}
			else
			{
				if (delta_y > 0)
					*wall_dir = DIR_S;
				else
					*wall_dir = DIR_N;
				*wall_x = g;
				*wall_y = ny;
			}
			is_hit = TRUE;
			// printf("Hit Wall!!\n");
			break ;
		}
		if (hit_side == VERT)
			nx += delta_x;
		else
			ny += delta_y;
	}
	return (is_hit);
}

double	cast_single_ray(t_view *vu, int x, double px, double py, double theta)
{
	double	ray;
	dir_t	wall_dir;
	double	wall_x;
	double	wall_y;
	double	wall_dist;

	ray = (theta + FOVH_2) - (x * ANGLE_PER_PIXEL);
	if (get_wall_intersection(ray, px, py, &wall_dir, &wall_x, &wall_y) == FALSE)
		return (INFINITY);
	wall_dist = l2dist(px, py, wall_x, wall_y);
	wall_dist *= cos(theta - ray);
	vu->wl.wall_x = wall_x;
	vu->wl.wall_y = wall_y;
	vu->wl.wall_dir = wall_dir;
	return (wall_dist);
}

void	my_mlx_pixel_put(t_view *vu, int x, int y_start, int y_end, int color)
{
	char	*dst;
	int		start_point;

	start_point = y_start;
	while (start_point < y_end)
	{
		dst = vu->addr + (start_point * vu->line_len + x * (vu->bpp / 8));
		*(unsigned int *)dst = color;
		start_point++;
	}
}

int	get_wall_height(double dist)
{
	double	fov_h;

	fov_h = 2.0 * dist * tan(FOV_V/2.0);
	return ((int)(SY * (WALL_H / fov_h)));
}

void	draw_wall(t_view *vu, double wall_dist, int x, int color)
{
	int	wall_height;
	int	y0;
	int	y1;
	int	y_start;
	int	y_end;

	wall_height = get_wall_height(wall_dist);
	y0 = (int)((SY - wall_height) / 2.0);
	y1 = y0 + wall_height - 1;
	y_start = max(0, y0);
	y_end = min(SY - 1, y1);
	my_mlx_pixel_put(vu, x, y_start, y_end, color);
}

void	put_pixel(t_view *vu, int x, int y, int color)
{
	char	*dst;

	dst = vu->addr + (y * vu->line_len + x * (vu->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_wall_texture(t_view *vu, int tx, int ty)
{
	int	ret;

	ret = vu->tex.texture[(vu->tex.px_wid * ty) + tx];
	// ret = 0xffaaff;
	return (ret);
}

void	draw_wall_by_xpm(t_view *vu, int x, double wall_dist)
{
	// draw pixels by xpm and wall distance;
	double	texture_ratio;
	int		tx;
	int		ty;
	int		wall_height;
	int		y0;
	int		y1;
	int		y_start;
	int		y_end;
	int		color;

	if (vu->wl.wall_dir == DIR_W || vu->wl.wall_dir == DIR_E)
		texture_ratio = vu->wl.wall_y - floor(vu->wl.wall_y);
	else
		texture_ratio = vu->wl.wall_x - floor(vu->wl.wall_x);
	tx = (int)(texture_ratio * vu->tex.px_wid);
	wall_height = get_wall_height(wall_dist);
	y0 = (int)((SY - wall_height) / 2.0);
	y1 = y0 + wall_height - 1;
	y_start = max(0, y0);
	y_end = min(SY - 1, y1);
	while (y_start <= y_end)
	{
		ty = (int)((double)(y_start - y0) * vu->tex.px_hei / wall_height);
		color = get_wall_texture(vu, tx, ty);
		put_pixel(vu, x, y_start, color);
		y_start++;
	}
}

void	render(t_view *vu)
{
	// static int	wall_colors[] = {0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb};
	int		x;			/* ? */

	x = 0;
	while (x < SX)
		my_mlx_pixel_put(vu, x++, 0, SY - 1, 0X000000);
	x = 0;
	while (x < SX)
	{
		vu->wl.wall_dist = cast_single_ray(vu, x, vu->px, vu->py, vu->theta);
		draw_wall_by_xpm(vu, x, vu->wl.wall_dist);
		x++;
	}
	mlx_put_image_to_window(vu->mlx, vu->mlx_win, vu->img, 0, 0);
}

int	get_move_offset\
(double theta, int keycode, double amt, double *delta_x, double *delta_y)
{
	if (keycode == W)
	{
		*delta_x = 1 * amt * cos(theta);
		*delta_y = 1 * amt * sin(theta);
	}
	else if (keycode == A)
	{
		*delta_x = amt * cos(theta + (1 * M_PI_2));
		*delta_y = amt * sin(theta + (1 * M_PI_2));
	}
	else if (keycode == S)
	{
		*delta_x = -1 * amt * cos(theta);
		*delta_y = -1 * amt * sin(theta);
	}
	else if (keycode == D)
	{
		*delta_x = amt * cos(theta + (-1 * M_PI_2));
		*delta_y = amt * sin(theta + (-1 * M_PI_2));
	}
	else
		return (1);
	return (0);
}

int	move_player(t_view *vu, int keycode, double amt)
{
	double	delta_x;
	double	delta_y;
	double	new_x;
	double	new_y;

	if (get_move_offset(vu->theta, keycode, amt, &delta_x, &delta_y))
		return (print_err("invalid key press"));
	new_x = vu->px + delta_x;
	new_y = vu->py + delta_y;
	if (map_get_cell((int)new_x, (int)new_y) != 0)
		return (print_err("bump"));
	vu->px = new_x;
	vu->py = new_y;
	render(vu);
	return (0);
}

void	rotate_player(t_view *vu, double delta)
{
	vu->theta += delta;
	if (vu->theta < 0)
		vu->theta += _2PI;
	else if (vu->theta > _2PI)
		vu->theta -= _2PI;
	render(vu);
}

int	key_down_event(int keycode, t_view *vu)
{
	if (keycode == W || keycode == A || keycode == S || keycode == D)
	{
		// move player coord;
		move_player(vu, keycode, MOVE_UNIT);
	}
	else if (keycode == LEFT || keycode == RIGHT)
	{
		// rotate player's view;
		if (keycode == LEFT)
			rotate_player(vu, ROT_UNIT * 1);
		else
			rotate_player(vu, ROT_UNIT * (-1));
	}
	else if (keycode == ESC)
	{
		printf("Exit\n");
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_view	vu;

	if (argc != 4)
		return (print_err("argument error"));
	vu.px = atof(argv[1]);
	vu.py = atof(argv[2]);
	vu.theta = deg2rad(atof(argv[3]));
	vu.mlx = mlx_init();
	vu.mlx_win = mlx_new_window(vu.mlx, SX, SY, "ray_casting tuto");
	vu.img = mlx_new_image(vu.mlx, SX, SY);
	vu.addr = mlx_get_data_addr(vu.img, &vu.bpp, &vu.line_len, &vu.endian);
	vu.tex.img_path = "./texture/red_brick_wall.xpm";
	vu.tex.px_wid = 64;
	vu.tex.px_hei = 64;
	vu.tex.img_ptr = mlx_xpm_file_to_image(vu.mlx, vu.tex.img_path, &vu.tex.px_wid, &vu.tex.px_hei);
	vu.tex.texture = (int *)(mlx_get_data_addr(vu.tex.img_ptr, &vu.tex.tex_bpp, &vu.tex.tex_line_len, &vu.tex.tex_endian));
	render(&vu);
	// move and draw;
	mlx_hook(vu.mlx_win, 2, 0, key_down_event, &vu);
	mlx_loop(vu.mlx);
	return (0);
}
