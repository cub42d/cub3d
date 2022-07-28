#include "ray_casting.h"

/**
 * @brief 주어진 좌표의 맵 블록을 확인
 * map[x][y] 형식으로 직접 접근할때 인덱스가 유효하지 않은 경우 segfault가
 * 생길 수 있기 때문에 이런 함수를 별도로 만들었음
 *
 * @param x 확인하고자 하는 맵 블록의 x좌표
 * @param y 확인하고자 하는 맵 블록의 y좌표
 * @return int : 주어진 좌표가 유효한 인덱스인 경우 해당 블록을 반환. 아닐시 -1 반환
 */
int	map_get_cell(int x, int y)
{
	if (x >= 0 && x < MAPX && y >= 0  && y < MAPY)
		return (map[x][y]);
	else
		return (-1);
}

/**
 * @brief 주어진 인자가 양수인지, 음수인지 혹은 0에 가까운 작은 수인지 판별하는 함수
 * is_zero(), EPS는 부동소수점 실수가 0인지 알아보는것이 정수와 다르기 때문에 사용함
 * (IEEE 754, 'machine epsilon' 참조)
 *
 * @param d
 * @return int : 0에 가까운 경우 0, 양수는 1, 음수는 -1을 반환
 */
int	num_sign(double d)
{
	if (is_zero(d))
		return (0);
	else if (d > 0)
		return (1);
	else
		return (-1);
}

/**
 * @brief 좌표상 두 점의 거리를 계산하는 함수
 *
 * @param x0 시작점 (x0, y0)의 x좌표
 * @param y0 시작점 (x0, y0)의 y좌표
 * @param x1 끝점 (x1, y1)의 x좌표
 * @param y1 끝점 (x1, y1)의 y좌표
 * @return double : 두 점의 거리를 반환
 */
double	l2dist(double x0, double y0, double x1, double y1)
{
	double	dx;
	double	dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}

/**
 * @brief 현낌 제작: 인자 str를 출력하고 1을 반환하는 함수
 * main 함수안에서 exit(1)을 하기 전 메시지를 출력할때 쓰려고 만들었음
 *
 * @param str 출력하고자 하는 (에러)메시지
 * @return int : 언제나 1을 반환
 */
int	print_err(char *str)
{
	printf("%s\n", str);
	return (1);
}

double	get_next_coord(int delta, double next_coord, double player_coord)
{
	if (delta > 0)
		next_coord = floor(player_coord) + 1;
	else
	{
		if (delta < 0)
			next_coord = ceil(player_coord) - 1;
		else
			next_coord = player_coord;
	}
	return(next_coord);
}

/**
 * @brief dda ray 에 쓰일 변수의 초기화를 함
 *
 * @param vu 게임의 정보가 들어있는 구조체
 * @param dda dda 계산을 위한 변수가 들어있는 구조체
 * @param ray 플레이어로 부터 발사된 ray 한줄기 (single ray)
 */
void	init_dda(t_view *vu, t_dda *dda, double ray)
{
	dda->delta_x = num_sign(cos(ray));
	dda->delta_y = num_sign(sin(ray));
	if (dda->delta_x == 0)
		dda->x_slope = INFINITY;
	else
		dda->x_slope = tan(ray);
	if (dda->delta_y == 0)
		dda->y_slope = INFINITY;
	else
		dda->y_slope = 1./tan(ray);
	dda->nx = get_next_coord(dda->delta_x, dda->nx, vu->px);
	dda->ny = get_next_coord(dda->delta_y, dda->ny, vu->py);
	dda->f_x = INFINITY;
	dda->g_x = INFINITY;
}

/**
 * @brief map 블록을 읽어오기 위해 map index와 가로, 세로선에 부딪혔는지 확인하는 함수
 *
 * @param vu 게임의 정보가 들어있는 구조체
 * @param dda  dda 계산을 위한 변수가 들어있는 구조체
 */
void	get_map_x_y(t_view *vu, t_dda *dda)
{
	if (dda->delta_x != 0)
		dda->f_x = dda->x_slope * (dda->nx - vu->px) + vu->py;
	if (dda->delta_y != 0)
		dda->g_x = dda->y_slope * (dda->ny - vu->py) + vu->px;
	dda->dist_verti = l2dist(vu->px, vu->py, dda->nx, dda->f_x);
	dda->dist_horiz = l2dist(vu->px, vu->py, dda->g_x, dda->ny);
	if (dda->dist_verti < dda->dist_horiz)
	{
		if (dda->delta_x == 1)
			dda->map_x = (int)dda->nx;
		else
			dda->map_x = (int)(dda->nx - 1);
		dda->map_y = (int)dda->f_x;
		dda->hit_side = VERT;
	}
	else
	{
		dda->map_x = (int)dda->g_x;
		if (dda->delta_y == 1)
			dda->map_y = (int)dda->ny;
		else
			dda->map_y = (int)(dda->ny - 1);
		dda->hit_side = HORIZ;
	}
}

/**
 * @brief ray가 닿은 벽의 위치와 방향을 저장하는 함수
 *
 * @param vu
 * @param dda
 */
void	get_ray_wall_var(t_view *vu, t_dda *dda)
{
	/* 부딪힌 방향이 세로선인 경우 */
	if (dda->hit_side == VERT)
	{
		/* ??? */
		if (dda->delta_x > 0)
			vu->wl.wall_dir = DIR_W;
		else
			vu->wl.wall_dir = DIR_E;
		vu->wl.wall_x = dda->nx;
		vu->wl.wall_y = dda->f_x;
	}
	else
	{
		if (dda->delta_y > 0)
			vu->wl.wall_dir = DIR_S;
		else
			vu->wl.wall_dir = DIR_N;
		vu->wl.wall_x = dda->g_x;
		vu->wl.wall_y = dda->ny;
	}
}

/**
 * @brief 주어진 인자들을 기반으로 인자 ray가 벽에 (어느 부분에 ) 부딪히는지 판별하는 함수
 *
 * @param vu 게임의 정보를 담고 있는 구조체
 * @param ray 화면의 가로 x값에 따른 빛줄기의 각도
 * @return int : 해당 ray가 벽에 부딪혔다면 1(True), 아니면 0(False)를 반환
 */
int	get_wall_intersection(t_view *vu, double ray)
{
	t_dda	dda;		/* dda algorithm 계산을 위한 구조체 */
	int		cell;
	int		is_hit;

	init_dda(vu, &dda, ray);
	is_hit = FALSE;
	while (!is_hit)
	{
		get_map_x_y(vu, &dda);
		cell = map_get_cell(dda.map_x, dda.map_y);
		if (cell < 0)
			break ;
		if (cell == 1)
		{
			get_ray_wall_var(vu, &dda);
			is_hit = TRUE;
			break ;
		}
		if (dda.hit_side == VERT)
			dda.nx += dda.delta_x;
		else
			dda.ny += dda.delta_y;
	}
	return (is_hit);
}

/**
 * @brief 주어진 인자로 벽과의 거리를 잴 ray 하나를 생성하는 함수
 *
 * @param vu 게임 내 정보를 담는 구조체
 * @param x 전체 화면의 x번째 가로 픽셀
 * @param px 플레이어의 x좌표
 * @param py 플레이어의 y좌표
 * @param theta 플레이어의 현재 시점각 (방향각)
 * @return double : ray를 쏴서 계산한 플레이어와 벽 간의 거리
 */
double	cast_single_ray(t_view *vu, int x, double theta)
{
	double	ray;

	/* 전체 시야각(FOVH??)에서 x??번째 ray의 기울기를 ray 변수에 저장 */
	/* 이해가 안되는게 왜 이걸 화면의 가로에서 모두 구하는건가? */
	ray = (theta + FOVH_2) - (x * ANGLE_PER_PIXEL);
	/* 벽과 닿지 않았다면 플레이어와의 거리로 무한을 반환 */
	if (get_wall_intersection(vu, ray) == FALSE)
		return (INFINITY);
	vu->wl.wall_dist = l2dist(vu->px, vu->py, vu->wl.wall_x, vu->wl.wall_y);
	/* 시점에 의해 어안효과가 나타나는것을 cos 함수로 보정해줌 */
	vu->wl.wall_dist *= cos(theta - ray);
	/* 텍스쳐 적용이 된 벽을 그리기 위해 get_wall_intersection에서 구한 wall_x, wall_y,
	wall_dir를 구조체에 저장함. */
	return (vu->wl.wall_dist);
}

/**
 * @brief 화면의 가로 위치 x에 단색 수직선을 그리는 함수
 *
 * @param vu 게임 내 정보를 담고있는 구조체
 * @param x 픽셀 수직선의 x좌표
 * @param y_start 수직선의 y좌표 시작점
 * @param y_end 픽셀 수직선의 y좌표 끝점
 * @param color 그릴 픽셀 선의 색깔
 */
void	put_vertical_solid_color_line(t_view *vu, int x, int y_start, int y_end, int color)
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

/**
 * @brief 벽과의 거리를 기반으로 벽의 높이를 계산하는 함수
 *
 * @param dist 플레이어와 벽 사이의 거리
 * @return int : 주어진 인자를 수식에 넣어 벽의 높이를 int로 반환
 */
int	get_wall_height(double dist)
{
	double	fov_h;

	fov_h = 2.0 * dist * tan(FOV_V/2.0);
	return ((int)(SY * (WALL_H / fov_h)));
}

/**
 * @brief 벽과의 거리를 바탕으로 화면의 x에 color색을 가진 벽을 그리는 함수
 *
 * @param vu 게임의 정보가 담긴 구조체
 * @param wall_dist 플레이어와 벽과의 거리
 * @param x 픽셀을 그릴 화면의 가로 x좌표
 * @param color 그릴 벽의 색깔
 */
void	draw_solid_color_wall(t_view *vu, double wall_dist, int x, int color)
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
	put_vertical_solid_color_line(vu, x, y_start, y_end, color);
}

/**
 * @brief player가 움직일떄 마다 화면을 업데이트 해주기 위헤 천장과 바닥을 그리는 함수
 *
 * @param vu 천장, 바닥 색상에 대한 정보가 들어있는 구조체
 */
void	clear_screen(t_view *vu)
{
	int	x;		/* 화면의 x - 가로 픽셀을 반복하며 작업하기 위한 인댁스 */

	x = 0;
	while (x < SX)
	{
		/* 세로 0부터 전체 화면의 절반인 (SY / 2)만큼 천장 색깔로 칠함 */
		put_vertical_solid_color_line(vu, x, 0, SY / 2, vu->ceiling_colour);
		/* 전체 화면의 절반인 (SY / 2) 지점 부터 화면 끝 SY까지 바닥 색깔로 칠함 */
		put_vertical_solid_color_line(vu, x, SY / 2, SY, vu->floor_colour);
		x++;
	}
}

/**
 * @brief 주어진 인자 x에 color 색깔을 가진 픽셀 하나를 그려주는 함수
 *
 * @param vu 게임의 정보가 담긴 구조체
 * @param x 픽셀을 그릴 좌표 (x, y)의 x
 * @param y 픽셀을 그릴 좌표 (x, y)의 y
 * @param color 그릴 픽셀의 색깔
 */
void	put_pixel(t_view *vu, int x, int y, int color)
{
	char	*dst;

	dst = vu->addr + (y * vu->line_len + x * (vu->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief 텍스쳐 배열에서 (tx, ty)에 해당되는 픽셀 색상을 가져오는 함수
 *
 * @param tex 색상을 가져올 텍스쳐 구조체의 포인터
 * @param tx 가져올 텍스쳐의 x좌표
 * @param ty 가져올 텍스쳐의 y좌표
 * @return int : 좌표가 가리키는 해당 텍스쳐 내 색상 값을 반환
 */
int	get_wall_texture(t_tex *tex, int tx, int ty)
{
	int	ret;

	ret = tex->texture[(tex->px_wid * ty) + tx];
	return (ret);
}

/**
 * @brief xpm 텍스쳐 색상에 따라 벽과의 거리에 비례해 벽을 그려주는 함수
 *
 * @param vu 게임의 정보가 담긴 구조체
 * @param x 픽셀을 그릴 화면의 가로값, x값
 * @param wall_dist 플레이어와 벽의 거리
 */
void	draw_textured_wall(t_view *vu, int x, double wall_dist)
{
	t_tex	*wall_texture;
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
	wall_texture = &vu->tex_wall[vu->wl.wall_dir];
	tx = (int)(texture_ratio * wall_texture->px_wid);
	wall_height = get_wall_height(wall_dist);
	y0 = (int)((SY - wall_height) / 2.0);
	y1 = y0 + wall_height - 1;
	y_start = max(0, y0);
	y_end = min(SY - 1, y1);
	while (y_start <= y_end)
	{
		ty = (int)((double)(y_start - y0) * wall_texture->px_hei / wall_height);
		color = get_wall_texture(wall_texture, tx, ty);
		put_pixel(vu, x, y_start, color);
		y_start++;
	}
}

/**
 * @brief 천장, 바닥, 벽 등 플레이어의 화면을 그리는 함수
 *
 * @param vu 플레이어, 맵, 벽 정보가 담긴 구조체
 */
void	render(t_view *vu)
{
	int	x;		/* 화면의 x - 가로 픽셀을 반복하며 작업하기 위한 인댁스 */

	clear_screen(vu);
	x = 0;
	while (x < SX)
	{
		/* 플레이어와 벽 거리를 구하기 위해 ray를 쏜다 */
		vu->wl.wall_dist = cast_single_ray(vu, x, vu->theta);
		/* 그 벽 거리를 바탕으로 실제 벽을 그린다. */
		draw_textured_wall(vu, x, vu->wl.wall_dist);
		x++;
	}
	/* 최종적으로 그린 픽셀들을 이미지로 윈도우에 집어넣는다. */
	mlx_put_image_to_window(vu->mlx, vu->mlx_win, vu->img, 0, 0);
}

/**
 * @brief 입력받은 키값에 따라 플레이어가 움직일 변화량 - offset을 계산해주는 함수
 *
 * @param theta 플레이어의 현재 시점각 (방향각)
 * @param keycode 입력받은 키 값
 * @param amt 키 입력에 따른 최소기본이동값, move_unit
 * @param delta_x x값 변화량
 * @param delta_y y값 변화량
 * @return int : 키 값이 WASD인 경우 0을 반환, 기타 유효하지 않은 키 값의 경우 1을 반환
 */
int	get_move_offset(double theta, int keycode, double amt, double *delta_x, double *delta_y)
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

/**
 * @brief 입력된 키값에 따라 플레이어 좌표 px, py를 변경해주는 함수
 *
 * @param vu 플레이어 정보가 담긴 구조체
 * @param keycode 입력받은 키 값
 * @param amt 키 입력에 따른 최소기본이동값, move_unit
 * @return int : 이동에 성공시 0, 실패시 1
 */
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

/**
 * @brief 입력된 키 값에 따라 플레이어의 시야각(theta)을 변경해주는 함수
 *
 * @param vu 플레이어 정보가 담긴 구조체
 * @param delta 변화값
 */
void	rotate_player(t_view *vu, double delta)
{
	vu->theta += delta;
	if (vu->theta < 0)
		vu->theta += _2PI;
	else if (vu->theta > _2PI)
		vu->theta -= _2PI;
	render(vu);
}

/**
 * @brief 키 입력 이벤트에 따라 플레이어의 시점, 좌표를 업데이트 해주는 함수
 *
 * @param keycode 입력받은 키의 키값, 키 코드
 * @param vu 플레이어 정보가 담긴 구조체
 * @return int : 0  mlx_hook 프로토타입에 맞추기 위해 그냥 반환값을 설정함
 */
int	key_down_event(int keycode, t_view *vu)
{
	/* WASD의 경우 플레이어의 좌표를 업데이트 해줌 */
	if (keycode == W || keycode == A || keycode == S || keycode == D)
	{
		move_player(vu, keycode, MOVE_UNIT);
	}
	/* 화살표 좌, 우의 경우 플레이어의 시점만 회전시킴. */
	else if (keycode == LEFT || keycode == RIGHT)
	{
		if (keycode == LEFT)
			rotate_player(vu, ROT_UNIT * 1);
		else
			rotate_player(vu, ROT_UNIT * (-1));
	}
	/* esc의 경우 게임을 종료시킴 */
	else if (keycode == ESC)
	{
		printf("Exit\n");
		exit(0);
	}
	return (0);
}

/**
 * @brief 벽 텍스쳐를 가져오는 함수
 *
 * @param vu 게임의 정보를 담는 구조체
 * @param img_dir 가져올 텍스쳐 이미지의 디렉토리 위치 문자열
 * @param i enum dir_t에 상응하는 인덱스 값 - while문을 위해 임시로 넣은 인자
 */
void	define_wall_texture(t_view *vu, char *img_dir, int i)
{
	vu->tex_wall[i].img_path = img_dir;
	vu->tex_wall[i].px_wid = 64;
	vu->tex_wall[i].px_hei = 64;
	vu->tex_wall[i].img_ptr = mlx_xpm_file_to_image(vu->mlx, \
	vu->tex_wall[i].img_path, &vu->tex_wall[i].px_wid, &vu->tex_wall[i].px_hei);
	vu->tex_wall[i].texture = (int *)(mlx_get_data_addr(\
	vu->tex_wall[i].img_ptr, &vu->tex_wall[i].tex_bpp, \
	&vu->tex_wall[i].tex_line_len, &vu->tex_wall[i].tex_endian));
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
	define_wall_texture(&vu, "./texture/red_brick_wall.xpm", 0);
	define_wall_texture(&vu, "./texture/grey_wall.xpm", 1);
	define_wall_texture(&vu, "./texture/steel_wall.xpm", 2);
	define_wall_texture(&vu, "./texture/blue_wall.xpm", 3);
	vu.floor_colour = 0x333333;
	vu.ceiling_colour = 0x777777;
	render(&vu);
	// move and draw;
	mlx_hook(vu.mlx_win, 2, 0, key_down_event, &vu);
	mlx_loop(vu.mlx);
	return (0);
}
