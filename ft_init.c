/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:38:41 by hgu               #+#    #+#             */
/*   Updated: 2024/01/27 14:01:44 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_xpm_files(t_info *info)
{
	int	flag;

	flag = 0;
	if (info->east.img == NULL)
		flag += printf("Error!: East wall xpm tesxture file is wrong\n");
	if (info->west.img == NULL)
		flag += printf("Error!: West wall xpm tesxture file is wrong\n");
	if (info->south.img == NULL)
		flag += printf("Error!: South wall xpm tesxture file is wrong\n");
	if (info->north.img == NULL)
		flag += printf("Error!: North wall xpm tesxture file is wrong\n");
	if (flag)
		exit(1);
	return ;
}

void	init_info(t_info *info, t_ray *ray)
{
	info->max_col = 0;
	info->cam.x = 640;
	info->mlx = mlx_init();
	info->mlx_win = mlx_new_window(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, \
	"MLX created");
	info->img.img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info->img.addr = mlx_get_data_addr(info->img.img, \
	&info->img.bits_per_pixel, &info->img.line_length, &info->img.endian);
	info->ray = ray;
}

void	init_user(t_user *user, t_info *info)
{
	locate_user(info->map, info);
	user->dir_x = 0;
	user->dir_y = 0;
	user->plane_x = 0;
	user->plane_y = 0;
	if (info->map[(int)user->pos_y][(int)user->pos_x] == 'N')
		user->dir_y = -1;
	else if (info->map[(int)user->pos_y][(int)user->pos_x] == 'S')
		user->dir_y = 1;
	else if (info->map[(int)user->pos_y][(int)user->pos_x] == 'W')
		user->dir_x = -1;
	else if (info->map[(int)user->pos_y][(int)user->pos_x] == 'E')
		user->dir_x = 1;
	if (user->dir_x == 0)
		user->plane_x = user->dir_y * (-0.66); //크기가 0.66인 이유에 대해서는 모르겠음
	else if (user->dir_y == 0)
		user->plane_y = user->dir_x * (0.66);
	user->plane_len = sqrt(pow(user->plane_x, 2) + pow(user->plane_y, 2));
	printf("user : dir_x : %f dir_y : %f plane_x : %f plane_y : %f\n", user->dir_x, user->dir_y, user->plane_x, user->plane_y);
}

void	init_flag(t_parse_flag *flag)
{
	flag->east = 0;
	flag->west = 0;
	flag->south = 0;
	flag->north = 0;
	flag->ceiling = 0;
	flag->floor = 0;
	flag->map_start_line = 0;
	flag->user_char = 0;
	return ;
}
