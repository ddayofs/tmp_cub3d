/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:47:33 by hgu               #+#    #+#             */
/*   Updated: 2023/09/07 20:07:05 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_so_long.h"

void	ft_error(char *str)
{
	ft_printf("Error\n");
	ft_printf("%s ", str);
	exit(1);
}

char	*ft_strdup(char *s1)
{
	int		idx;
	char	*s2;

	idx = 0;
	while (s1[idx])
		idx++;
	s2 = malloc(idx + 1);
	idx = 0;
	while (s1[idx])
	{
		s2[idx] = s1[idx];
		idx++;
	}
	s2[idx] = '\0';
	return (s2);
}

int	ft_close(t_param *par)
{
	free(par->map);
	ft_printf("exit the game");
	exit(0);
}

void	p_to_c_dfs(int x, int y, char *map_tmp, t_param *par)
{
	if (map_tmp[x + y * par->map_col] == 'C')
		par->c_cnt++;
	if (map_tmp[x + y * par->map_col] == '1' || \
	map_tmp[x + y * par->map_col] == 'E')
		return ;
	else
		map_tmp[x + y * par->map_col] = '1';
	p_to_c_dfs(x + 1, y, map_tmp, par);
	p_to_c_dfs(x, y + 1, map_tmp, par);
	p_to_c_dfs(x - 1, y, map_tmp, par);
	p_to_c_dfs(x, y - 1, map_tmp, par);
}

void	p_to_e_dfs(int x, int y, char *map_tmp, t_param *par)
{
	if (map_tmp[x + y * par->map_col] == 'E')
		par->e_cnt++;
	if (map_tmp[x + y * par->map_col] == '1')
		return ;
	else
		map_tmp[x + y * par->map_col] = '1';
	p_to_e_dfs(x + 1, y, map_tmp, par);
	p_to_e_dfs(x, y + 1, map_tmp, par);
	p_to_e_dfs(x - 1, y, map_tmp, par);
	p_to_e_dfs(x, y - 1, map_tmp, par);
}
