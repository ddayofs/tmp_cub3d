/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:33:59 by donglee2          #+#    #+#             */
/*   Updated: 2023/07/31 20:05:40 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	if (str[0] == 0)
		return (0);
	if (str[++i] != c)
		count++;
	while (str[++i])
		if (str[i - 1] == c && str[i] != c)
			count++;
	return (count);
}

static char	*copy_str(char const *str, char c, int *s_idx)
{
	char	*ret2_str;
	int		word_len;
	int		j;

	word_len = 0;
	j = 0;
	while (str[word_len] && str[word_len] != c)
		word_len++;
	*s_idx += word_len;
	ret2_str = (char *)malloc (sizeof(char) * (word_len + 1));
	if (ret2_str == NULL)
		return (NULL);
	while (j < word_len)
	{
		ret2_str[j] = str[j];
		j++;
	}
	ret2_str[j] = 0;
	return (ret2_str);
}

static char	**ft_freeall(char **ret_str)
{
	int	idx;

	idx = -1;
	while (ret_str[++idx])
		free(ret_str[idx]);
	free(ret_str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ret_str;
	int		i;
	int		ret_str_i;

	ret_str = (char **)malloc(sizeof(char *) * (words_count(s, c) + 1));
	if (ret_str == NULL)
		return (NULL);
	i = 0;
	ret_str_i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		if (s[i])
		{
			ret_str[ret_str_i] = copy_str(&s[i], c, &i);
			if (ret_str[ret_str_i] == NULL)
				return (ft_freeall(ret_str));
			ret_str_i++;
		}
	}
	ret_str[ret_str_i] = NULL;
	return (ret_str);
}
