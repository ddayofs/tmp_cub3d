/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:42:02 by hgu               #+#    #+#             */
/*   Updated: 2024/01/27 17:11:03 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dx_dy(int *dx, int *dy)
{
	dx[0] = 1;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 0;
	dx[4] = 1;
	dx[5] = 1;
	dx[6] = -1;
	dx[7] = -1;
	dy[0] = 0;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = -1;
	dy[4] = 1;
	dy[5] = -1;
	dy[6] = -1;
	dy[7] = 1;
}

void	locate_user(char **map, t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i] != NULL)
	//while (++i < info->row_cnt)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' \
			|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				printf("posy:%f posx:%F\n", info->user->pos_y, info->user->pos_x);
				info->user->pos_y = (double)i;
				info->user->pos_x = (double)j;
				return ;
			}
		}
	}
	printf("No user in the map\n");
	exit(1);
}

void	fill_space(char *map, int max)
{
	int	len;

	len = ft_strlen(map) - 1;
	while (len < max)
		map[len++] = ' ';
	map[max - 1] = '\0';
	return ;
}

void	free_dbptr(char **dbptr)
{
	int	i;

	i = -1;
	while (dbptr[++i])
		free(dbptr[i]);
	free(dbptr);
}

int	validation_error(char *error_msg, char **splits, char *line)
{
	if (splits != NULL)
		free_dbptr(splits);
	free(line);
	printf("%s\n", error_msg);
	return (1);
}
