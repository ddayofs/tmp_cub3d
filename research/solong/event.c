/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:52:50 by hgu               #+#    #+#             */
/*   Updated: 2024/01/13 15:40:31 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

int	key_press(int keycode, t_param *param)
{
	if (keycode == KEY_W)
		check_p_space(param, param->x / 64, (param->y - param->hei) / 64);
	else if (keycode == KEY_S)
		check_p_space(param, param->x / 64, (param->y + param->hei) / 64);
	else if (keycode == KEY_A)
		check_p_space(param, (param->x - param->wid) / 64, param->y / 64);
	else if (keycode == KEY_D)
		check_p_space(param, (param->x + param->wid) / 64, param->y / 64);
	else if (keycode == KEY_ESC)
		ft_close(param);
	return (0);
}

void	check_p_space(t_param *par, int x, int y)
{
	if (par->map[y * par->map_col + x] == '0' || \
	par->map[y * par->map_col + x] == 'P')
	{
		par->x = x * 64;
		par->y = y * 64;
		ft_printf("move : %d\n", ++par->move);
	}
	else if (par->map[y * par->map_col + x] == 'E' && \
	par->get_c == par->real_c_cnt)
	{
		ft_printf("move : %d\nEscape the world!\n", ++par->move);
		par->x = x * 64;
		par->y = y * 64;
		free(par->map);
		exit(0);
	}
	else if (par->map[y * par->map_col + x] == 'C')
	{
		par->x = x * 64;
		par->y = y * 64;
		par->get_c++;
		par->map[y * par->map_col + x] = '0';
		ft_printf("move : %d\n", ++par->move);
		ft_printf("you got collection\n");
	}
}

void	draw_map(t_param *p)
{
	int	r;
	int	c;

	r = -1;
	while (++r < p->map_row)
	{
		c = -1;
		while (++c < p->map_col)
		{
			if (p->map[r * p->map_col + c] == '1')
				mlx_put_image_to_window(p->mlx, p->win, p->w, c * 64, r * 64);
			else if (p->map[r * p->map_col + c] == '0')
				mlx_put_image_to_window(p->mlx, p->win, p->g, c * 64, r * 64);
			else if (p->map[r * p->map_col + c] == 'C')
				mlx_put_image_to_window(p->mlx, p->win, p->c, c * 64, r * 64);
			else if (p->map[r * p->map_col + c] == 'E')
				mlx_put_image_to_window(p->mlx, p->win, p->e, c * 64, r * 64);
			else if (p->map[r * p->map_col + c] == 'P')
				mlx_put_image_to_window(p->mlx, p->win, p->g, c * 64, r * 64);
		}
	}
}

int	draw(t_param *par)
{
	mlx_clear_window(par->mlx, par->win);
	draw_map(par);
	mlx_put_image_to_window(par->mlx, par->win, par->p, par->x, par->y);
	return (0);
}
