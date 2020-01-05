/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:52:15 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/18 14:56:55 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_thread(t_rt *specs, t_thread data[], int n)
{
	int		i;

	data[0] = (t_thread){.y_start = 0,
		.y_end = specs->h_img / n, .specs = specs};
	i = 0;
	while (++i < n)
	{
		data[i] = (t_thread){.y_start = data[i - 1].y_end,
		.y_end = (i + 1) * specs->h_img / n, .specs = specs};
	}
}

static void	join_threads(pthread_t ids[], int last)
{
	int				i;

	i = -1;
	while (++i < last)
		pthread_join(ids[i], NULL);
}

void		launch_threads(t_rt *specs, int n)
{
	pthread_t		ids[n];
	t_thread		data[n];
	pthread_attr_t	attr;
	int				i;

	pthread_attr_init(&attr);
	init_thread(specs, data, n);
	i = -1;
	while (++i < n)
	{
		if (pthread_create(&(ids[i]), &attr, pixel_loop, &data[i]) != 0)
		{
			join_threads(ids, i);
			exit_protocol2(specs, 0, "Failed to create pthread");
		}
	}
	join_threads(ids, n);
}
