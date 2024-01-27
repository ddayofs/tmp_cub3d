/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:04:07 by hgu               #+#    #+#             */
/*   Updated: 2024/01/27 16:14:54 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	select_tex_pixel(t_line *line, t_ray *ray, t_data *tex, t_user *user)
{
	double	wallx; //레이가 벽의 어느 지점에 부딪히는지 알려주는 비율 

	if (ray->side == WALL_X)
		wallx = user->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else if (ray->side == WALL_Y)
		wallx = (double)user->pos_x + \
		(double)ray->perp_wall_dist * (double)ray->ray_dir_x;
	wallx = wallx - floor(wallx);
	line->tex_x_point = (int)(wallx * TEX_WIDTH);
	if (ray->side == WALL_X && ray->ray_dir_x > 0)
		line->tex_x_point = TEX_WIDTH - line->tex_x_point - 1;
	if (ray->side == WALL_Y && ray->ray_dir_y < 0)
		line->tex_x_point = TEX_WIDTH - line->tex_x_point - 1;
}

void	draw_vertical(t_line line, t_ray *ray, t_info *info, t_data *tex)
{
	char	*target_ptr;
	int		y;
	double	step; //보이는 벽의 높이와 실제텍스처의 비율이 다르므로 조절하기위한 상수
	double	tex_pos; //텍스처의 y위치

	y = -1;
	while (++y < line.draw_start)
		my_mlx_pixel_put(&(info->img), (int)ray->x, y, info->c_color);
	step = 1.0 * (double)TEX_HEIGHT / (double)line.height;
	tex_pos = (line.draw_start - SCREEN_HEIGHT / 2 + line.height / 2) * step;
	while (y <= line.draw_end)
	{
		if (tex_pos >= TEX_HEIGHT)
			tex_pos = TEX_HEIGHT - 1;
		if (tex_pos < 0)
			tex_pos = 0;
		target_ptr = tex->addr + tex->line_length * (int)tex_pos + (TEX_WIDTH - \
		line.tex_x_point) * (tex->bits_per_pixel / 8);
		my_mlx_pixel_put(&(info->img), (int)ray->x, y, \
		*(unsigned int *)target_ptr);
		tex_pos += step;
		y++;
	}
	while (y < SCREEN_HEIGHT)
		my_mlx_pixel_put(&(info->img), (int)ray->x, y++, info->f_color);
}
