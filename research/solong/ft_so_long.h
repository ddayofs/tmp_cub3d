/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:38:11 by hgu               #+#    #+#             */
/*   Updated: 2023/09/11 18:45:54 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SO_LONG_H
# define FT_SO_LONG_H

# include <fcntl.h>
# include "mlx.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define KEY_ESC			53
# define KEY_W				13
# define KEY_S				1
# define KEY_A				0
# define KEY_D				2
# define PRESS_RED_BUTTON	17

typedef struct s_param
{
	void	*mlx;
	void	*win;
	void	*c;
	void	*g;
	void	*e;
	void	*p;
	void	*w;
	int		fd;
	int		x;
	int		y;
	int		wid;
	int		hei;
	int		map_col;
	int		map_row;
	int		real_c_cnt;
	int		get_c;
	int		p_cnt;
	int		c_cnt;
	int		e_cnt;
	int		move;
	char	*map;
	int		flag;
}	t_param;

void	init_param(t_param *param, char *map);
void	init_map_data(t_param *param, char *map_name);
int		key_press(int keycode, t_param *param);
int		draw(t_param *param);
void	check_map_name(char *str);
void	check_map_shape(t_param *param, char *gnl);
char	*ft_strdup(char *s1);
void	check_p_space(t_param *par, int x, int y);
int		ft_close(t_param *param);
void	check_closed_wall(t_param *par, char *map);
void	check_rule(t_param *par, char *map_name);
void	p_to_e_dfs(int x, int y, char *map_tmp, t_param *par);
void	p_to_c_dfs(int x, int y, char *map_tmp, t_param *par);
void	check_p_c_e(t_param *par);
void	check_player(t_param *par);
#endif