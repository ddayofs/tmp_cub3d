/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:40:35 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/27 16:46:31 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_info *info, double angle)
{
	int		new_x;
	int		new_y;
	double	new_plane_x;
	double	new_plane_y;

	new_x = info->user->dir_x * cos(angle) - info->user->dir_y * sin(angle);
	new_y = info->user->dir_x * sin(angle) + info->user->dir_y * cos(angle);
	new_plane_x = info->user->plane_x * cos(angle) \
	- info->user->plane_y * sin(angle);
	new_plane_y = info->user->plane_x * sin(angle) \
	+ info->user->plane_y * cos(angle);
	info->user->dir_x = new_x;
	info->user->dir_y = new_y;
	info->user->plane_x = new_plane_x;
	info->user->plane_y = new_plane_y;
}

void	rotate_left(t_info *info, double angle)
{
	int		new_x;
	int		new_y;
	double	new_plane_x;
	double	new_plane_y;

	new_x = info->user->dir_x * cos(-angle) \
	- info->user->dir_y * sin(-angle);
	new_y = info->user->dir_x * sin(-angle) \
	+ info->user->dir_y * cos(-angle);
	new_plane_x = info->user->plane_x * cos(-angle) \
	- info->user->plane_y * sin(-angle);
	new_plane_y = info->user->plane_x * sin(-angle) \
	+ info->user->plane_y * cos(-angle);
	info->user->dir_x = new_x;
	info->user->dir_y = new_y;
	info->user->plane_x = new_plane_x;
	info->user->plane_y = new_plane_y;
}