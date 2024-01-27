/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:00:16 by hgu               #+#    #+#             */
/*   Updated: 2024/01/27 16:34:46 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	raycasting(t_info *info, t_user *user, t_ray *ray)
{
	t_line	line;

	ray->map_x = (int)user->pos_x;
	ray->map_y = (int)user->pos_y;
	ray->x = 0;
	while (ray->x < SCREEN_WIDTH)
	{
		ray->camera_x = (2 * ray->x) / SCREEN_WIDTH - 1;
		ray->ray_dir_x = user->dir_x + user->plane_x * ray->camera_x;
		ray->ray_dir_y = user->dir_y + user->plane_y * ray->camera_x;
		init_dist(info, user, ray);
		perform_dda(info, user, ray, 0);
		line = init_line_height(info, user, ray);
		draw_line(line, user, ray, info);
		ray->x += 1;
	}
	return (0);
}

void	init_dist(t_info *info, t_user *user, t_ray *ray)
{
	ray->map_x = (int)user->pos_x;
	ray->map_y = (int)user->pos_y;
	ray->deltadist_x = 1e30;
	ray->deltadist_y = 1e30;
	if (ray->ray_dir_x != 0)
		ray->deltadist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y != 0)
		ray->deltadist_y = fabs(1 / ray->ray_dir_y);
	ray->step_x = 1;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (user->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
		ray->sidedist_x = (ray->map_x + 1 - user->pos_x) * ray->deltadist_x;
	ray->step_y = 1;
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (user->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
		ray->sidedist_y = (ray->map_y + 1 - user->pos_y) * ray->deltadist_y;
}

void	perform_dda(t_info *info, t_user *user, t_ray *ray, int hit)
{
	while (!hit)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = WALL_X;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = WALL_Y;
		}
		if (info->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->side == WALL_X)
		ray->perp_wall_dist = ray->sidedist_x - ray->deltadist_x;
	else
		ray->perp_wall_dist = ray->sidedist_y - ray->deltadist_y;
	if (ray->perp_wall_dist == 0)
		ray->perp_wall_dist = 0.1;
}

t_line	init_line_height(t_info *info, t_user *user, t_ray *ray)
{
	t_line	line;

	line.height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	line.draw_start = SCREEN_HEIGHT / 2 - line.height / 2;
	if (line.draw_start < 0)
		line.draw_start = 0;
	line.draw_end = SCREEN_HEIGHT / 2 + line.height / 2;
	if (line.draw_end >= SCREEN_HEIGHT)
		line.draw_end = SCREEN_HEIGHT - 1;
	return (line);
}

void	draw_line(t_line line, t_user *user, t_ray *ray, t_info *info)
{
	t_data	tex;

	if (ray->side == WALL_X)
	{
		if ((double)ray->map_x < user->pos_x)
			tex.img = info->west.img;
		else
			tex.img = info->east.img;
	}
	else
	{
		if ((double)ray->map_y < user->pos_y)
			tex.img = info->north.img;
		else
			tex.img = info->south.img;
	}
	tex.addr = mlx_get_data_addr(tex.img, &(tex.bits_per_pixel), \
	&(tex.line_length), &(tex.endian));
	select_tex_pixel(&line, ray, &tex, user);
	draw_vertical(line, ray, info, &tex);
}
