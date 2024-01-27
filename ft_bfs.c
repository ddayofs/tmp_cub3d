/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:29:45 by hgu               #+#    #+#             */
/*   Updated: 2024/01/27 17:16:39 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**map_copy(char **src, t_info *info, int i, int j)
{
	char	**dst;

	dst = (char **)malloc(sizeof(char *) * info->row_cnt + 1);
	if (dst == NULL)
		exit(1);
	dst[info->row_cnt] = NULL;
	while (src[++i])
	{
		j = -1;
		dst[i] = malloc(info->max_col);
		if (dst[i] == NULL)
			exit(1);
		while (src[i][++j])
			dst[i][j] = src[i][j];
		j = -1;
		while (dst[i][++j] == ' ')
			dst[i][j] = '*';
		j = info->max_col - 2;
		while (dst[i][j] == ' ' || dst[i][j] == '\n')
			dst[i][j--] = '*';
		dst[i][info->max_col - 1] = '\0';
	}
	return (dst);
}

int	check_zero(char **copy_map, int new_x, int new_y)
{
	if (copy_map[new_y][new_x] == '0')
		return (1);
	return (0);
}

int	check_space(char **copy_map, int new_x, int new_y)
{
	if (copy_map[new_y][new_x] == ' ')
		return (1);
	return (0);
}

int	check_visited(char **copy_map, int new_x, int new_y, t_info *info)
{
	if (new_y < 0 || new_x < 0)
		ft_exit("out\n");
	if (new_y > info->row_cnt - 1|| new_x > info->max_col - 1)
		ft_exit("out\n");
	if (copy_map[new_y][new_x] == 'v')
		return (1);
	return (0);
}

void	ft_bfs(t_queue *q, t_info *info, int *dx, int *dy)
{
	int		i;
	char	**copy_map;
	int		new_x;
	int		new_y;

	copy_map = map_copy(info->map, info, -1, -1);
	while (!is_empty(q))
	{
		i = -1;
		while (++i < 8)
		{
			new_x = q->first->x + dx[i];
			new_y = q->first->y + dy[i];
			printf("row_cnt[%d] max_col : [%d]\n", info->row_cnt, info->max_col);
			printf("new_y : [%d] new_x[%d]\n\n", new_y, new_x);
			if (copy_map[new_y][new_x] == ' ' || copy_map[new_y][new_x] == '*') //여기서 걸리는데
			{
				printf("map_condition_error %d %d\n", new_y, new_x);
				printf("map[%d][%d] == [%c]\n", new_y, new_x, copy_map[new_y][new_x]);
				free_dbptr(copy_map);
				exit(1);
			}
			if (!check_visited(copy_map, new_x, new_y, info) && check_zero(copy_map, new_x, new_y)) //방문한 적이 없고, '0'이라면 q에 push 한다.
			{
				push(&q, q->first->x + dx[i], q->first->y + dy[i]);
				copy_map[new_y][new_x] = 'v';
			}
		}
		pop(&q);
	}
	free_dbptr(copy_map);
}

void	check_edge(t_info *info, int *dx, int *dy)
{
	//맵복사 //앞에서 내부검사에 썻던 copy를 free해주는 과정이 필요하다
	info->copy_map = map_copy(info->map, info, -1, -1);
	//1째줄검사
	check_first_line(info, dx, dy); //bfs한번돌리고
	//마지막줄검사
	check_last_line(info, dx, dy); //또돌리고
	//제일왼쪽 검사
	check_left_line(info, dx, dy);
	//제일 오른쪽 검사
	check_right_line(info, dx, dy);
}

void	check_left_line(t_info *info, int *dx, int *dy)
{
	t_queue	*q;
	int		idx;
	int		x;

	q = NULL;
	while (idx < info->row_cnt - 1)
	{
		x = -1;
		// while (info->copy_map[idx][++x] == '*') //각 행의 왼쪽부터 *인 부분을 스킵한다
		// 	;
		if (info->copy_map[idx][++x] == '0')
		{
			printf("map_condition_error\n");
            exit(1);
		}
		else if (info->copy_map[idx][x] == ' ')
		{
			push(&q, x, idx);
			space_bfs(&q, info, dx, dy);
		}
		else if (info->copy_map[idx][x] == '*')
		{
			push(&q, x, idx);
			space_bfs(&q, info, dx, dy);
		}
		idx++;
	}
}

void	check_right_line(t_info *info, int *dx, int *dy)
{
	t_queue	*q;
	int		idx;
	int		x;

	idx = 0;
	q = NULL;
	while (idx < info->row_cnt - 1)
	{
		x = info->max_col - 1;
		// while (info->copy_map[idx][--x] == '*')
		// 	;
		if (info->copy_map[idx][--x] == '0')
		{
			printf("right\n");
			printf("map_condition_error\n");
            exit(1);
		}
		else if (info->copy_map[idx][x] == ' ')
		{
			push(&q, x, idx);
			space_bfs(&q, info, dx, dy);
		}
		else if (info->copy_map[idx][x] == '*')
		{
			push(&q, x, idx);
			space_bfs(&q, info, dx, dy);
		}
		idx++;
	}
}

void	check_first_line(t_info *info, int *dx, int *dy)
{
	t_queue	*q;
	int		idx;

	idx = -1;
	q = NULL;
	// while (info->copy_map[0][++idx] == '*')
	// 	;
	while (++idx < info->max_col - 1)
	{
		if (info->copy_map[0][idx] == '0')
		{
			printf("first\n");
			printf("map_condition_error\n");
			exit (1);
		}
		else if (info->copy_map[0][idx] == ' ')
		{
			push(&q, idx, 0);
			space_bfs(&q, info, dx, dy);
		}
		else if (info->copy_map[0][idx] == '*')
		{
			printf("first\n");
			push(&q, idx, 0);
			space_bfs(&q, info, dx, dy);
		}
		//idx++;
	}
}

void	check_last_line(t_info *info, int *dx, int *dy)
{
	t_queue	*q;
	int		idx;

	idx = -1;
	q = NULL;
	// while (info->copy_map[info->row_cnt - 1][++idx] == '*')
	// 	;
	printf("row_cnt : %d\n", info->row_cnt);
	while (idx < info->max_col - 1)
	{
		if (info->copy_map[info->row_cnt - 1][++idx] == '0')
		{
			printf("last\n");
			printf("map_condition_error\n");
			exit(1);
		}
		else if (info->copy_map[info->row_cnt - 1][idx] == ' ')
		{
			printf("last\n");
			printf("idx : %d, row_cnt : %d\n", idx, info->row_cnt);
			push(&q, idx, info->row_cnt - 1); //여기서 터짐
			space_bfs(&q, info, dx, dy);
		}
		idx++;
	}
}

void	space_bfs(t_queue **q, t_info *info, int *dx, int *dy)
{
	int	i;
	int	new_x;
	int	new_y;

	while (!is_empty(*q))
	{
		if (info->copy_map[(*q)->first->y][(*q)->first->x] == '0')
		{
			printf("x : %d y : %d %c\n",(*q)->first->x,(*q)->first->y, info->copy_map[(*q)->first->y][(*q)->first->x]);
			printf("map_condition_error\n");
			exit(1);
		}
		info->copy_map[(*q)->first->y][(*q)->first->x] = 'v';
		i = -1;
		while (++i < 8)
		{
			new_x = (*q)->first->x + dx[i];
			new_y = (*q)->first->y + dy[i];
			if (new_x < 0 || new_y < 0 || new_x > info->max_col - 2 || new_y > info->row_cnt - 1)
				continue ;
			if (info->copy_map[new_y][new_x] != 'v' && info->copy_map[new_y][new_x] != '1')
				push(q, new_x, new_y);
		}
		pop(q);
	}
}
