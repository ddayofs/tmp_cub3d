/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 21:38:57 by hgu               #+#    #+#             */
/*   Updated: 2024/01/09 18:08:39 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

void	check_gnl(t_param *param, char *gnl)
{
	int		idx;

	idx = -1;
	if (!gnl)
		ft_error("empty file");
	param->map_col = ft_strlen(gnl) - 1;
	if (gnl[param->map_col] != '\n')
		ft_error("less than 3 lines ");
	param->map_row = 0;
	param->map = malloc(param->map_col + 1);
	while (gnl[++idx] != '\n')
		param->map[idx] = gnl[idx];
	param->map[idx] = '\0';
	param->wid = 64;
	param->hei = 64;
}

void	init_map_data(t_param *param, char *map_name)
{
	char	*gnl;

	param->fd = open(map_name, O_RDONLY);
	if (param->fd <= 0)
		ft_error("map open ");
	gnl = get_next_line(param->fd);
	check_gnl(param, gnl);
	while (gnl)
	{
		param->map_row++;
		if (ft_strlen(gnl) < 3 || ft_strlen(gnl) > 127)
			ft_error("column");
		check_map_shape(param, gnl);
		free(gnl);
		gnl = get_next_line(param->fd);
		if (gnl)
			param->flag = 0;
		if (gnl != NULL && gnl[ft_strlen(gnl) - 1] == '\n')
			param->flag = 1;
		param->map = ft_strjoin(param->map, gnl, param->map_col);
	}
	free(gnl);
	if (param->map_row < 3 || param->map_row > 127)
		ft_error("row");
}

void	init_param(t_param *par, char *map)
{
	int	idx;

	idx = -1;
	while (map[++idx])
	{
		if (map[idx] == 'P')
			break ;
	}
	par->x = idx % par->map_col * 64;
	par->y = idx / par->map_col * 64;
	par->mlx = mlx_init();
	par->win = NULL;
	par->real_c_cnt = 0;
	par->get_c = 0;
	par->move = 0;
	par->c = mlx_xpm_file_to_image(\
	par->mlx, "textures/c.xpm", &par->wid, &par->hei);
	par->e = mlx_xpm_file_to_image(\
		par->mlx, "textures/e.xpm", &par->wid, &par->hei);
	par->p = mlx_xpm_file_to_image(\
		par->mlx, "textures/p.xpm", &par->wid, &par->hei);
	par->g = mlx_xpm_file_to_image(\
		par->mlx, "textures/g.xpm", &par->wid, &par->hei);
	par->w = mlx_xpm_file_to_image(\
	par->mlx, "textures/w.xpm", &par->wid, &par->hei);
}

int	main(int argc, char *argv[])
{
	t_param	par;

	if (argc != 2)
	{
		ft_error("arg ");
	}
	check_map_name(argv[1]);
	init_map_data(&par, argv[1]);
	init_param(&par, par.map);
	check_rule(&par, argv[1]);
	par.win = mlx_new_window(\
	par.mlx, par.map_col * 64, par.map_row * 64, "Ddong game");
	mlx_loop_hook(par.mlx, &draw, &par);
	mlx_hook(par.win, PRESS_RED_BUTTON, 0, &ft_close, &par);
	mlx_key_hook(par.win, &key_press, &par);
	mlx_loop(par.mlx);
	free(par.map);
	exit(0);
}

void	check_rule(t_param *par, char *map_name)
{
	char	*map_tmp;
	int		x;
	int		y;

	if (!par->c || !par->p || !par->e || !par->g || !par->w)
	{
		free(par->map);
		ft_error("mlx return is 0");
	}
	x = par->x / 64;
	y = par->y / 64;
	if (par->flag == 1)
	{
		free(par->map);
		ft_error("last line is only nl ");
	}
	check_player(par);
	check_closed_wall(par, par->map);
	map_tmp = ft_strdup(par->map);
	p_to_c_dfs(x, y, map_tmp, par);
	free(map_tmp);
	map_tmp = ft_strdup(par->map);
	p_to_e_dfs(x, y, map_tmp, par);
	free(map_tmp);
	check_p_c_e(par);
}
