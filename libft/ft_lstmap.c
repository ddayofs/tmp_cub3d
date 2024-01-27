/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:54:36 by donglee2          #+#    #+#             */
/*   Updated: 2023/05/31 18:13:01 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp_node;
	void	*tmp_content;

	if (!lst || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		tmp_content = (*f)(lst->content);
		tmp_node = ft_lstnew(tmp_content);
		if (!tmp_node)
		{
			del(tmp_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, tmp_node);
		lst = lst->next;
	}
	return (new_lst);
}
