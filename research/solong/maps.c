/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:08:51 by hgu               #+#    #+#             */
/*   Updated: 2023/09/07 19:20:21 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

void	check_map_name(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
	{
		ft_error("map name ");
	}
	if (str[len - 1] != 'r' && str[len - 2] != 'e')
	{
		ft_error("map name ");
	}
	if (str[len - 3] != 'b' && str[len - 4] != '.')
	{
		ft_error("map name ");
	}
}

void	check_map_shape(t_param *param, char *gnl)
{
	int	len;
	int	idx;

	len = ft_strlen(gnl);
	idx = -1;
	while (gnl[++idx])
	{
		if (gnl[idx] == '\n')
		{
			len -= 1;
			break ;
		}
		if (!(gnl[idx] == '0' || gnl[idx] == '1' || gnl[idx] == 'P' || \
		gnl[idx] == 'E' || gnl[idx] == 'C'))
		{
			ft_error("Map value ");
		}
	}
	if (param->map_col != len)
		ft_error("Not rect ");
	return ;
}

void	check_closed_wall(t_param *par, char *map)
{
	int		len;
	int		idx;

	len = -1;
	while (par->map[++len])
	{
		if (par->map[len] == 'C')
			par->real_c_cnt++;
	}
	idx = -1;
	while (par->map[++idx])
	{
		if ((idx < par->map_col || idx >= len - par->map_col) \
		&& map[idx] != '1')
		{
			ft_error("Map is not closed ");
		}
		if ((idx % par->map_col == 0 || \
		idx % par->map_col == (par->map_col - 1)) && map[idx] != '1')
		{
			ft_error("Map is not closed ");
		}
	}
}

void	check_p_c_e(t_param *par)
{
	if (par->e_cnt != 1 || par->c_cnt != par->real_c_cnt || par->real_c_cnt < 1)
	{
		free(par->map);
		ft_error("no route to get collection or exit ");
	}
}

void	check_player(t_param *par)
{
	int	idx;

	idx = -1;
	par->p_cnt = 0;
	par->c_cnt = 0;
	par->e_cnt = 0;
	while (par->map[++idx])
	{
		if (par->map[idx] == 'P')
			par->p_cnt++;
	}
	if (par->p_cnt != 1)
	{
		free(par->map);
		ft_error("player nums ");
	}
}
