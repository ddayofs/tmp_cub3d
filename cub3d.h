/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:12:22 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/27 16:47:32 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>



# define SCREEN_WIDTH		1280
# define SCREEN_HEIGHT		720
# define TEX_WIDTH			340
# define TEX_HEIGHT			340
# define MAP_WIDTH			24
# define MAP_HEIGHT			24
# define KEY_ESC			53
# define KEY_W				13
# define KEY_S				1
# define KEY_A				0
# define KEY_D				2
# define KEY_LEFT			123
# define KEY_RIGHT			124
# define PRESS_RED_BUTTON	17
# define WALL_X				0
# define WALL_Y				1

typedef struct s_user
{
	double	pos_x; //현재유저의 x좌표
	double	pos_y; //현재유저의 y좌표
	double	dir_x; //유저가 바라보는 방향벡터의 x값
	double	dir_y; //유저가 바라보는 방향벡터의 y값
	//plane벡터란 plane평면의 중심에서 오른쪽끝으로 가는 방향벡터
	double	plane_x; //plane벡터의 x값
	double	plane_y; //plane벡터의 y값
	double	plane_len;
	double	fov;
}t_user;

typedef struct s_ray
{
	double	camera_x; //camera_x는 -1(왼쪽 끝)에서 1(오른쪽 끝)사이의 실수값
	double	ray_dir_x; //레이벡터의 x값
	double	ray_dir_y; //레이벡터의 y값
	double	sidedist_x; //시작지점에서 처음으로 x값이 정수가 되는 부분과 만나는 지점까지의 길이
	double	sidedist_y; //시작지점에서 처음으로 y값이 저수가 되는 부분과 만나는 지점까지의 길이
	double	deltadist_x; //처음으로 x값이 정수가 되는 부분에서부터 다음번 x가 정수가 되는 부분까지의 길이
	double	deltadist_y; //처음으로 y값이 정수가 되는 부분에서부터 다음번 y가 정수가 되는 부분까지의 길이
    double	perp_wall_dist; //어안렌즈 효과를 방지하기위한 수직거리
	double	x; //실제 윈도우창에서의 x픽셀번호
	int		step_x; //광선 x방향의 증감여부
	int		step_y; //광선 y방향의 증감여부
	int		map_x; //맵위에서 현재광선이 닿은 블록의 x좌표
	int		map_y; //맵상에서 현재유저가 위치한 박스위치?
	int		side; //광선이 x축과 y축중 어느축에 부딪히는지에 대한 플래그
	double	real_x; //광선이 실제로 닿은 블록의 x좌표의 정확한 지점
}t_ray;

typedef struct s_data
{
	void	*img; //찍어낼 최종이미지를 저장할 포인터변수
	char	*addr; //텍스처 픽셀 색상정보의 addr
	int		bits_per_pixel; //픽셀당 몇비트인지 addr함수로 초기화됨->offset계산에 사용
	int		line_length; //이미지의 라인길이를 아는법
	int		endian; //메모리에 색코드가 어떤 방식으로 저장되는지 플래그->addr함수로 초기화됨
	int		width; //텍스처이미지의 너비
	int		height; //텍스처이미지의 높이
}t_data;

typedef	struct	s_camera
{//마우스_hook을 위해서 사용하는 변수로 게임화면위에서 마우스의 x,y좌표를 저장한다?
	double	x;
	double	y;
}t_camera;

typedef struct s_info
{
	char		**map;
	char		**copy_map;
	int			max_col;
	t_data		img; //윈도우에 붙여넣을 이미지
	t_data		west;
	t_data		east;
	t_data		south;
	t_data		north;
	//char		*file_name; //map파일 이름(?) 사용여부 나중에 체크해봐야함
	void		*mlx;
	void		*mlx_win;
	//int			color; //사용여부 나중에 체크해봐야함 //no_texture인 상태로 테스트하는 경우에 사용했음
	int			f_color; //바닥 색상
	int			c_color; //천장 색상
	t_user		*user;
	t_ray		*ray;
	t_camera	cam;
	int			width;
	int			height;
	int			row_cnt;
}t_info;

typedef struct s_parse_flag
{
	int		east;
	int		west;
	int		south;
	int		north;
	int		ceiling;
	int		floor;
	int		map_start_line;
	char	user_char;
}t_parse_flag;

typedef struct s_line
{
	int		wall_height_pixel;
	int		height; //다르다?
	int		draw_start; //윈도우 화면에서 그려야하는 벽의 시작지점 픽셀번호
	int		draw_end; //윈도우 화면에서 그려야하는 벽의 끝픽셀번호
	int		tex_x_point;//벽의 x좌표에 대한 텍스처의 상대적x 좌표
	double	y_ratio; //그려야할 벽의 세로 길이 : 텍스쳐의 세로 길이 의 비율
	double	x_ratio;//그려야할 벽의 가로 길이 : 텍스쳐의 가로 길이 의 비율
	void	*cur_texture; //이번에 그려야하는 텍스처이미지
}t_line;

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*prev;
	struct s_node	*next;
}t_node;

typedef struct s_queue
{
	t_node	*first;
	t_node	*last;
}t_queue;

//parse.c
int		create_trgb(int red, int green, int blue);
int		make_map(int fd, t_info *info, char **line, t_parse_flag *flag);
int		parsing(char *argv, t_info *info);
int		check_tex_valid(int fd, t_info *info, t_parse_flag *flag, char **line);
int		check_map(int fd, t_info *info, char **line, t_parse_flag *flag);
void	is_map_closed(t_info *info);
void	check_comma(char *str);
//draw_pixel
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	select_tex_pixel(t_line *line, t_ray *ray, t_data *tex, t_user *user);
void	draw_vertical(t_line line, t_ray *ray, t_info *info, t_data *tex);
//ft_bfs
char	**map_copy(char **src, t_info *info, int i, int j);
int		check_zero(char **copy_map, int new_x, int new_y);
int		check_space(char **copy_map, int new_x, int new_y);
int		check_visited(char **copy_map, int new_x, int new_y, t_info *info);
void	ft_bfs(t_queue *q, t_info *info, int *dx, int *dy);
void	check_edge(t_info *info, int *dx, int *dy);
void	check_left_line(t_info *info, int *dx, int *dy);
void	check_right_line(t_info *info, int *dx, int *dy);
void	check_first_line(t_info *info, int *dx, int *dy);
void	check_last_line(t_info *info, int *dx, int *dy);
void	space_bfs(t_queue **q, t_info *info, int *dx, int *dy);
//ft_init
void	init_info(t_info *info, t_ray *ray);
void	init_user(t_user *user_ptr, t_info *info);
void	init_flag(t_parse_flag *flag);
//ft_queue
int		is_empty(t_queue *q);
t_queue	*init_queue(void);
t_node	*make_new_node(int x, int y);
void	push(t_queue **queue, int x, int y);
void	pop(t_queue **queue);
void	print_queue(t_queue *queue);
void	free_nodes_n_queue(t_queue *queue);
//key_hook_utils
void	rotate_right(t_info *info, double angle);
void	rotate_left(t_info *info, double angle);

//key_hook
int		key_handler(int key_code, t_info *info);
int		move_up_down(t_info *info, int key_code);
int		move_side(t_info *info, int key_code);
void	camera_rotate(t_info *info, int key_code);
//parse_condition_check
int		check_name(char *argv);
int		check_dir_valid(char **s, t_info *i, char *l, t_parse_flag *f);
int		check_c_f_valid(char **splits, t_info *info, \
		char *line, t_parse_flag *flag);
int		check_map_line_valid(char *line, t_parse_flag *flag);
int		check_flag(t_parse_flag *flag);
//parse_utils
void	init_dx_dy(int *dx, int *dy);
void	locate_user(char **map, t_info *info);
void	fill_space(char *map, int max);
void	free_dbptr(char **splits);
int		validation_error(char *error_msg, char **splits, char *line);
//ratcasting
int		raycasting(t_info *info, t_user *user, t_ray *ray);
void	init_dist(t_info *info, t_user *user, t_ray *ray);
void	perform_dda(t_info *info, t_user *user, t_ray *ray, int hit);
t_line	init_line_height(t_info *info, t_user *user, t_ray *ray);
void	draw_line(t_line line, t_user *user, t_ray *ray, t_info *info);
//
int		win_close(t_info *info);
int		check_wall(t_info *info, double mov_x, double mov_y);
void	ft_exit(char *str);
void	check_xpm_files(t_info *info);

#endif 