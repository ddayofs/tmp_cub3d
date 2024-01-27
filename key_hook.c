/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:24:39 by hgu               #+#    #+#             */
/*   Updated: 2024/01/27 16:48:36 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int key_code, t_info *info)
{
	if (key_code == 53)
		win_close(info);
	mlx_destroy_image(info->mlx, info->img.img);
	info->img.img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info->img.addr = mlx_get_data_addr(info->img.img, \
	&(info->img.bits_per_pixel), &(info->img.line_length), &(info->img.endian));
	if (key_code == KEY_W)
		move_up_down(info, key_code);
	else if (key_code == KEY_S)
		move_up_down(info, key_code);
	else if (key_code == KEY_A)
		move_side(info, key_code);
	else if (key_code == KEY_D)
		move_side(info, key_code);
	else if (key_code == KEY_LEFT)
		camera_rotate(info, key_code);
	else if (key_code == KEY_RIGHT)
		camera_rotate(info, key_code);
	printf("pos_x : %f pos_y : %f\n", info->user->pos_x, info->user->pos_y);
	if (raycasting(info, info->user, info->ray) == 1)
		return (1);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img.img, 0, 0);
	return (0);
}

int	move_up_down(t_info *info, int key_code)
{
	if (key_code == KEY_W)
	{
		if (check_wall(info, info->user->dir_x, info->user->dir_y) == 1)
			return (1);
		info->user->pos_x = info->user->pos_x + info->user->dir_x * 0.3;
		info->user->pos_y = info->user->pos_y + info->user->dir_y * 0.3;
	}
	else if (key_code == KEY_S)
	{
		if (check_wall(info, -info->user->dir_x, -info->user->dir_y) == 1)
			return (1);
		info->user->pos_x = info->user->pos_x - info->user->dir_x * 0.3;
		info->user->pos_y = info->user->pos_y - info->user->dir_y * 0.3;
	}
	if (info->user->pos_x == (int)info->user->pos_x)
		info->user->pos_x += 0.00001;
	if (info->user->pos_y == (int)info->user->pos_y)
		info->user->pos_y += 0.00001;
	return (0);
}

//반환형 void로 하면 norm 통과
int	move_side(t_info *info, int key_code)
{
	double	mov_x;
	double	mov_y;

	if (key_code == KEY_D)
	{
		mov_x = info->user->dir_x * cos(M_PI / 2) \
		- info->user->dir_y * sin(M_PI / 2);
		mov_y = info->user->dir_x * sin(M_PI / 2) \
		+ info->user->dir_y * cos(M_PI / 2);
	}
	else if (key_code == KEY_A)
	{
		mov_x = info->user->dir_x * cos(M_PI / 2) \
		+ info->user->dir_y * sin(M_PI / 2);
		mov_y = -info->user->dir_x * sin(M_PI / 2) \
		+ info->user->dir_y * cos(M_PI / 2);
	}
	printf("mov_x : %f mov_y : %f\n", mov_x, mov_y);
	if (check_wall(info, mov_x, mov_y) == 1)
		return (1);
	info->user->pos_x += mov_x * 0.3;
	info->user->pos_y += mov_y * 0.3;
	if (info->user->pos_x == (int)info->user->pos_x)
		info->user->pos_x += 0.000001;
	if (info->user->pos_y == (int)info->user->pos_y)
		info->user->pos_y += 0.000001;
	return (0);
}

void	camera_rotate(t_info *info, int key_code)
{
	double		new_x;
	double		new_y;
	double		new_plane_x;
	double		new_plane_y;
	double		angle;

	angle = M_PI / 60;
	if (key_code == KEY_RIGHT)
	{
		new_x = info->user->dir_x * cos(angle) - info->user->dir_y * sin(angle);
		new_y = info->user->dir_x * sin(angle) + info->user->dir_y * cos(angle);
		new_plane_x = info->user->plane_x * cos(angle) \
		- info->user->plane_y * sin(angle);
		new_plane_y = info->user->plane_x * sin(angle) \
		+ info->user->plane_y * cos(angle);
	}
		// rotate_right(info, angle);
	else if (key_code == KEY_LEFT)
		// rotate_left(info, angle);
	{
		new_x = info->user->dir_x * cos(-angle) \
		- info->user->dir_y * sin(-angle);
		new_y = info->user->dir_x * sin(-angle) \
		+ info->user->dir_y * cos(-angle);
		new_plane_x = info->user->plane_x * cos(-angle) \
		- info->user->plane_y * sin(-angle);
		new_plane_y = info->user->plane_x * sin(-angle) \
		+ info->user->plane_y * cos(-angle);
	}
	info->user->dir_x = new_x;
	info->user->dir_y = new_y;
	info->user->plane_x = new_plane_x;
	info->user->plane_y = new_plane_y;
}
