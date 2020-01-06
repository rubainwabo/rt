/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:47:56 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/24 16:50:30 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	if (alst != NULL)
	{
		if (*alst != NULL && del != NULL)
		{
			del((*alst)->content, (*alst)->content_size);
		}
		ft_memdel((void**)alst);
	}
}
