/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:35:15 by hgu               #+#    #+#             */
/*   Updated: 2024/01/27 16:25:15 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty(t_queue *q)
{
	if (q == NULL)
		return (1);
	if (q->first == NULL)
		return (1);
	return (0);
}

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (!queue)
	{
		printf("Error: Q malloc failed\n");
		exit(1);
	}
	queue->first = NULL;
	queue->last = NULL;
	return (queue);
}

t_node	*make_new_node(int x, int y)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		printf("Error: Node malloc failed\n");
		exit(1);
	}
	new_node->x = x;
	new_node->y = y;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	push(t_queue **queue, int x, int y)
{
	t_node	*node_to_push;

	if (*queue == NULL)
		*queue = init_queue();
	//printf("push : %d %d\n",x,y);
	node_to_push = make_new_node(x, y);
	if ((*queue)->first == NULL)
	{
		(*queue)->first = node_to_push;
		(*queue)->last = node_to_push;
	}
	else
	{
		(*queue)->last->next = node_to_push;
		node_to_push->prev = (*queue)->last;
		(*queue)->last = node_to_push;
	}
}

void	pop(t_queue **queue)
{
	t_node	*node;

	if (*queue == NULL || (*queue)->first == NULL) // 큐가 비어있는지 확인
	{
		//printf("queue is empty!!!!!!!!!!!\n");
		return ;
	}
	node = (*queue)->first;
	if ((*queue)->first == (*queue)->last) // 큐에 노드가 1개만 있어서 pop하면 큐가 비게되는 경우.
	{
		//printf("last node is poped\n");
		(*queue)->first = NULL;
		(*queue)->last = NULL;
		free(*queue);
		*queue = NULL; // 큐 포인터를 NULL로 설정
	}
	else
	{
		(*queue)->first = (*queue)->first->next;
		(*queue)->first->prev = NULL;
	}
	free(node); // 노드 메모리 해제
	return ;
}

//free_nodes_n_queue 큐에서 노드 다빼지 못할 경우 실행
void	free_nodes_n_queue(t_queue *queue)
{
	t_node	*cur_node;
	t_node	*tmp_node;

	if (queue == NULL)
		return ;
	if (queue->first != NULL)
	{
		cur_node = queue->first;
		while (cur_node != NULL)
		{
			tmp_node = cur_node;
			cur_node = cur_node->next;
			free(tmp_node);
		}
	}
	free(queue);
}

void	print_queue(t_queue *queue)
{
	t_node	*node;
	int		cnt;

	printf("print_queue started\n");
	cnt = 0;
	if (queue == NULL)
	{
		printf("que is NULL\n");
		printf("print_queue end\n");
		return ;
	}
	node = queue->first;
	while (node != NULL)
	{
		printf("idx: %d: x == %d, y == %d\n", cnt, node->x, node->y);
		node = node->next;
		cnt++;
	}
	printf("print_queue end\n");
}

// int	main(void)
// {
// 	t_queue	*queue;

// 	atexit(leak);
// 	queue = NULL;
// 	push(&queue, 1, 2);
// 	push(&queue, 3, 4);
// 	push(&queue, 5, 6);
// 	push(&queue, 7, 8);
// 	print_queue(queue);
// 	// pop(&queue);
// 	// printf("--------------------deque----\n");
// 	// print_queue(queue);
// 	// pop(&queue);
// 	// printf("--------------------deque----\n");
// 	// print_queue(queue);
// 	// pop(&queue);
// 	// printf("--------------------deque----\n");
// 	// print_queue(queue);
// 	// pop(&queue);
// 	// printf("--------------------deque----\n");
// 	// printf("here\n");
// 	// print_queue(queue);
// 	// pop(&queue);
// 	// printf("--------------------deque----\n");
// 	// print_queue(queue);
// 	// pop(&queue);
// 	// printf("--------------------deque----\n");
// 	// print_queue(queue);
// 	// pop(&queue);
// 	// printf("--------------------deque----\n");
// 	print_queue(queue);
// 	free_nodes_n_queue(queue);
// }
