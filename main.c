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

double	cast_single_ray(int x, double px, double py, double theta, dir_t *dir)
{
	double	ray;
	dir_t	wall_dir;
	double	wall_x;
	double	wall_y;
	double	wall_dist;

	(void)dir;
	ray = (theta + FOVH_2) - (x * ANGLE_PER_PIXEL);
	if (get_wall_intersection(ray, px, py, &wall_dir, &wall_x, &wall_y) == FALSE)
		return (INFINITY);
	wall_dist = l2dist(px, py, wall_x, wall_y);
	wall_dist *= cos(theta - ray);
	return (wall_dist);
}

void	my_mlx_pixel_put(t_data *data, int x, int y_start, int y_end, int color)
{
	char	*dst;
	int		start_point;

	start_point = y_start;
	while (start_point < y_end)
	{
		dst = data->addr + (start_point * data->line_len + x * (data->bits_per_pixel / 8));
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

void	draw_wall(t_data *data, double wall_dist, int x, int color)
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
	my_mlx_pixel_put(data, x, y_start, y_end, color);
}

// void	render(void *mlx, void *mlx_win, t_data *data, coord_t *player_coord)
// {
// 	static int	wall_colors[] = {0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb};
// 	int		x;			/* ? */

// 	mlx_clear_window(mlx, mlx_win);
// 	x = 0;
// 	while (x < SX)
// 	{
// 		wall_dist = cast_single_ray(x, px, py, theta, &wall_dir);
// 		draw_wall(&img, wall_dist, x, 0X75B9A0);
// 		x++;
// 	}
// }

int	main(int argc, char **argv)
{
	double	px;			/* player x */
	double	py;			/* player y */
	double	theta;		/* angle of fov */
	double	wall_dist;	/* wall distance from player */
	dir_t	wall_dir;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	px = atof(argv[1]);
	py = atof(argv[2]);
	theta = deg2rad(atof(argv[3]));
	if (argc != 4)
		return (print_err("argument error"));
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SX, SY, "ex03 :The Height");
	img.img = mlx_new_image(mlx, SX, SY);
	img.addr = mlx_get_data_addr\
	(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	int		x;			/* ? */

	mlx_clear_window(mlx, mlx_win);
	x = 0;
	while (x < SX)
	{
		wall_dist = cast_single_ray(x, px, py, theta, &wall_dir);
		draw_wall(&img, wall_dist, x, 0X75B9A0);
		x++;
	}
	/*
	*	mlx_hook(mlx_win, key_code, 0, event_func, void *param);
	*/
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
