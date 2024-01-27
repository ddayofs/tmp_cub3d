/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_condition_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:22:34 by hgu               #+#    #+#             */
/*   Updated: 2024/01/27 16:34:50 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_name(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (len < 4)
		return (0);
	if (argv[len - 1] != 'b' && argv[len - 2] != 'u' \
	&& argv[len - 3] != 'c' && argv[len - 4] != '.')
		return (1);
	return (0);
}

int	set_img(t_data *dir, t_info *info, char *str, int *flag_dir)
{
	dir->img = mlx_xpm_file_to_image\
	(info->mlx, str, &(dir->width), &(dir->height));
	if (*flag_dir == 1)
        ft_exit("Error: Duplicate declaration error.");	
	*flag_dir = 1;
	printf("test\n");
	return (0);
}

int	check_dir_valid(char **splits, t_info *info, char *line, t_parse_flag *flag)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (set_img(&(info->north), info, splits[1], &(flag->north)));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (set_img(&(info->south), info, splits[1], &(flag->south)));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (set_img(&(info->west), info, splits[1], &(flag->west)));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		return (set_img(&(info->east), info, splits[1], &(flag->east)));
	}
	return (1);
}

int	check_c_f_valid(char **splits, t_info *info, char *line, t_parse_flag *flag)
{
	char	**color_splits;

	if (line[0] == 'C' && line[1] == ' ' && splits[2] == NULL)
	{
		check_comma(splits[1]);
		color_splits = ft_split(splits[1], ',');
		if (color_splits[0] != NULL && color_splits[1] != NULL && color_splits[2] != NULL)
			info->c_color = create_trgb(ft_atoi(color_splits[0]), ft_atoi(color_splits[1]), ft_atoi(color_splits[2]));
		else
			ft_exit("Error : color format is wrong\n");
		flag->ceiling = 1;
		free_dbptr(color_splits);
		return (0);
	}
	else if (line[0] == 'F' && line[1] == ' ' && splits[2] == NULL)
	{
		check_comma(splits[1]);
		color_splits = ft_split(splits[1], ',');
		if (color_splits[0] != NULL && color_splits[1] != NULL && color_splits[2] != NULL)
			info->f_color = create_trgb(ft_atoi(color_splits[0]), ft_atoi(color_splits[1]), ft_atoi(color_splits[2]));
		else
			ft_exit("Error : color format is wrong\n");
		flag->floor = 1;
		free_dbptr(color_splits);
		return (0);
	}
	return (1);
}

int	check_map_line_valid(char *line, t_parse_flag *flag)
{
	int	i;

	i = -1;
	if (line[0] == '\n')
	{
		// prntf("here*****************\n");
		return (1); //오류인경우
	}
	while (line[++i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			if (flag->user_char != 0) //여기
				ft_exit("Error : There are 2 or more users!!\n");
			flag->user_char = line[i];
		}
		if (line[i] == ' ' || line[i] == '1' || \
		line[i] == '0' || line[i] == 'N' || \
		line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || line[i] == '\n')
			continue ;
		else
			return (1);
	}
	return (0);
}

int	check_flag(t_parse_flag *flag)
{
	if (flag->east == 0 || flag->west == 0 || flag->south == 0 || flag->north == 0 || flag->ceiling == 0 || flag->floor == 0)
		return (0);
	return (1);
}
