/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:57:10 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/27 16:33:37 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int red, int green, int blue)
{
	int	color;

	if (red > 255 || green > 255 || blue > 255 || red < 0 || \
	green < 0 || blue < 0)
	{
		printf("invalid color value\n");
		exit (1);
	}
	red = red << 16;
	green = green << 8;
	blue = blue;
	color = red + green + blue;
	return (color);
}

int	make_map(int fd, t_info *info, char **line, t_parse_flag *flag)
{
	int	i;

	free(*line);
	i = -1;
	while (++i < flag->map_start_line)
	{
		*line = get_next_line(fd);
		free(*line);
	}
	*line = get_next_line(fd);
	i = 0;
	while (*line)
	{
		info->map[i] = (char *)malloc(sizeof(char) * (info->max_col));
		if (info->map[i] == NULL)
			exit(1); //나중에 수정필요
		ft_strlcpy(info->map[i], *line, info->max_col); // + 1을 하지 않으면 제일 긴 길이의 행들은 개행없이 널문자까지만 복사됨
		if (ft_strlen(*line) < info->max_col - 1)
			fill_space(info->map[i], info->max_col);
		free(*line);
		*line = get_next_line(fd);
		i++;
	}
	return (0);
}

int	parsing(char *argv, t_info *info)
{
	int				fd;
	t_parse_flag	flag;
	char			*line;

	if (check_name(argv))
		ft_exit("Error : not a .cub file\n");
	init_flag(&flag);
	info->row_cnt = 0;
	info->max_col = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_exit("Error : no such file\n");
	if (check_tex_valid(fd, info, &flag, &line) || \
	check_map(fd, info, &line, &flag))
	{
		close(fd);
		ft_exit("Error : .cub file is not valid\n");
	}
	close (fd);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_exit("Error : no such file\n");
	make_map(fd, info, &line, &flag);
	close(fd);
	return (0);
}

void	check_comma(char *str)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str == ',')
			cnt++;
		str++;
	}
	if (cnt != 2)
		ft_exit("Error : color format is wrong\n");
}

int	check_tex_valid(int fd, t_info *info, t_parse_flag *flag, char **line)
{
	char			**splits;

	*line = get_next_line(fd);
	while (*line && check_flag(flag) == 0)
	{
		flag->map_start_line++;
		(*line)[ft_strlen(*line) - 1] = '\0';
			splits = ft_split(*line, ' ');
		if (splits[1] != NULL && splits[2] == NULL)
		{
			if (check_dir_valid(splits, info, *line, flag) \
			&& check_c_f_valid(splits, info, *line, flag))
				return (validation_error\
				("unexpected file value", splits, *line));
		}
		if (splits[0] != NULL && splits[1] == NULL)
			ft_exit("unexpecte line\n");
		free_dbptr(splits);
		free (*line);
		*line = get_next_line(fd);
	}
	if (*line == NULL)
		return (validation_error("file error", NULL, NULL));
	return (0);
}

int	check_map(int fd, t_info *info, char **line, t_parse_flag *flag)
{
	while ((*line)[0] == '\n')
	{
		free (*line);
		*line = get_next_line(fd);
		flag->map_start_line++;
	}
	while (*line)
	{
		printf("flag : %p\n", flag);
		printf("%s", *line);
		if (check_map_line_valid(*line, flag))
			return (validation_error("map error\n", NULL, *line));
		if (info->max_col < ft_strlen(*line))
			info->max_col = ft_strlen(*line);
		free (*line);
		*line = get_next_line(fd);
		(info->row_cnt)++;
	}
	info->map = (char **)malloc(sizeof(char *) * (info->row_cnt + 1));
	if (info->map == NULL)
		return (1);
	info->map[info->row_cnt] = NULL;
	return (0);
}

void	is_map_closed(t_info *info)
{
	t_queue	*q;
	int		idx;
	int		dx[8];
	int		dy[8];

	init_dx_dy(dx, dy);
	q = NULL;
	idx = -1;
	locate_user(info->map, info);
	check_edge(info, dx, dy);
	push(&q, (int)(info->user->pos_x), (int)(info->user->pos_y));
	ft_bfs(q, info, dx, dy);
	//free_dbptr(info->copy_map);
	//free_nodes_n_queue(q); //여긴데
	//check_edge(info, dx, dy);
	//free_nodes_n_queue(q);
}
