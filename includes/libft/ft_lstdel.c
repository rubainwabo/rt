/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:52:31 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/29 18:22:15 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*tmp;

	if (alst != NULL && del != NULL)
	{
		while (*alst)
		{
			tmp = (*alst)->next;
			ft_lstdelone(alst, del);
			*alst = tmp;
		}
	}
}
