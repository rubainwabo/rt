/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_protocol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:33:18 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/06 18:24:38 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_array(char **array, int index, t_rt *specs, char *line)
{
	ft_putendl("Failed to read input file");
	free(line);
	while (--index >= 0)
		free(array[index]);
	free(array);
	mlx_destroy_window(specs->mlx, specs->win);
	exit(0);
}

/*
** p == 0 -> free surface and cache of the last created object
** p == 2 -> free only the cache
** p == 19 -> exit when escape is pressed
*/

void	exit_protocol(t_rt *specs, int p, char *err)
{
	int i;

	ft_putendl_fd(err, 2);
	mlx_destroy_window(specs->mlx, specs->win);
	if (p == 0)
	{
		free_surface(specs->cache_id, specs->cache);
		free(specs->cache);
	}
	if (p == 2)
		free(specs->cache);
	free_all_lists(specs);
	i = -1;
	while (++i < specs->nb_line)
		free(specs->input[i]);
	free(specs->input);
	exit(EXIT_FAILURE);
}

void	exit_protocol2(t_rt *specs, int p, char *err)
{
	if (p == 19)
		ft_putendl(err);
	else
		ft_putendl_fd(err, 2);
	free_all_lists(specs);
   	destroy_img(specs, specs->img_s);
   	destroy_img(specs, specs->ui);
	mlx_destroy_window(specs->mlx, specs->win);
	if (p == 19)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}