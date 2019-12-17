/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 20:55:39 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/29 19:23:41 by krutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_w(const char *s, char c)
{
	int		count;
	int		sub;

	sub = 0;
	count = 0;
	while (*s != '\0')
	{
		if (sub == 1 && *s == c)
			sub = 0;
		if (sub == 0 && *s != c)
		{
			sub = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static void	ft_freetab(char **str, int i)
{
	while (i > 0)
		free(str[i--]);
	free(str);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**t;
	int		nb_word;
	int		i;

	i = 0;
	t = NULL;
	if (s == NULL)
		return (NULL);
	nb_word = count_w((const char*)s, c);
	if (!(t = (char**)malloc(sizeof(*t) * (count_w((const char*)s, c) + 1))))
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		if (!(t[i] = ft_strsub((const char*)s, 0, word_len((const char*)s, c))))
		{
			ft_freetab(t, i);
			return (NULL);
		}
		s = s + word_len(s, c);
		i++;
	}
	t[i] = NULL;
	return (t);
}
