/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:10:39 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/27 16:30:40 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_info *info, double mov_x, double mov_y)
{
	int	x;
	int	y;

	x = info->user->pos_x + mov_x;
	y = info->user->pos_y + mov_y;
	printf("check_wall x : %d y : %d\n",x,y);
	if (info->map[y][x] == '1')
		return (1);
	return (0);
}

int	win_close(t_info *info)
{
	mlx_destroy_window(info->mlx, info->mlx_win);
	free_dbptr(info->map);
	exit(0);
}

int	mouse_handler(int x, int y, t_info *info)
{
	double		new_x;
	double		new_plane_x;
	double		angle;

	if (x >= info->cam.x && x < SCREEN_WIDTH && y >= 0 && y < 720)
		angle = M_PI / 60;
	else if (x >= 0 && x < info->cam.x && y >= 0 && y < 720)
		angle = -M_PI / 60;
	else
		return (1);
	new_x = info->user->dir_x * cos(angle) - info->user->dir_y * sin(angle);
	info->user->dir_y = \
	info->user->dir_x * sin(angle) + info->user->dir_y * cos(angle);
	new_plane_x = info->user->plane_x * cos(angle) \
	- info->user->plane_y * sin(angle);
	info->user->plane_y = \
	info->user->plane_x * sin(angle) + info->user->plane_y * cos(angle);
	info->cam.x = x;
	info->user->dir_x = new_x;
	info->user->plane_x = new_plane_x;
	if (raycasting(info, info->user, info->ray) == 1)
		return (1);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img.img, 0, 0);
	return (0);
}

void	leak()
{
	system("leaks cub3d");
}

void	ft_exit(char *str)
{
	printf("%s", str);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_user	user;
	t_info	info;
	t_ray	ray;

	//atexit(leak);
	if (argc != 2)
	{
		printf("argc error\n");
		return (1);
	}
	info.user = &user;
	parsing(argv[1], &info);
	is_map_closed(&info);
	init_info(&info, &ray);
	init_user(&user, &info);
	check_xpm_files(&info);
	mlx_hook(info.mlx_win, 17, 0, &win_close, &info);
	mlx_hook(info.mlx_win, 2, 0, &key_handler, &info);
	mlx_hook(info.mlx_win, 6, 0, &mouse_handler, &info);
	if (raycasting(&info, &user, &ray) == 1)
		return (1);
	mlx_put_image_to_window(info.mlx, info.mlx_win, info.img.img, 0, 0);
	mlx_loop(info.mlx);
}

