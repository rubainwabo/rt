/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:14:15 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/06 19:41:38 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			count_line(int fd, t_rt *specs)
{
	int		test;
	int		count;
	char	*line;

	count = 0;
	while ((test = get_next_line(fd, &line)))
	{
		if (test == -1)
		{
			mlx_destroy_window(specs->mlx, specs->win);
			exit(1);
		}
		count++;
		free(line);
	}
	if (count == 0)
	{
		mlx_destroy_window(specs->mlx, specs->win);
		exit(1);
	}
	close(fd);
	specs->nb_line = count;
	return (count);
}

int			file_to_array(int fd, t_rt *specs, char **av)
{
	char		*line;
	int			i;
	int			j;

	i = -1;
	if (!(specs->input = (char **)malloc(sizeof(char *)
			* count_line(fd, specs) + 1)))
		return (0);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		free_array(specs->input, FAIL, specs, NULL);
	while ((j = get_next_line(fd, &line)))
	{
		if (j == -1)
			free_array(specs->input, i, specs, line);
		if (!(specs->input[++i] = (char *)malloc(sizeof(char) *
					ft_strlen(line) + 1)))
			free_array(specs->input, i, specs, line);
		j = -1;
		while (++j < (int)ft_strlen(line))
			specs->input[i][j] = line[j];
		specs->input[i][ft_strlen(line)] = '\0';
		free(line);
	}
	specs->input[i + 1] = NULL;
	return (1);
}

int			init_rt_struct(int fd, t_rt *new, char **av)
{
	if (!(new->mlx = mlx_init()))
		return (ft_error("mlx_init failed"));
	new->fct_ptr[0] = plane_intersect;
	new->fct_ptr[1] = sphere_intersect;
	new->fct_ptr[2] = cylinder_intersect;
	new->fct_ptr[3] = cone_intersect;
	if (!(new->win = mlx_new_window(new->mlx, WIDTH, HEIGHT, "rt")))
		return (ft_error("mlx_window init failed"));
	new->w_img = W_IMG / 2;
	new->h_img = H_IMG / 2;
	new->aspect = (double)W_IMG / H_IMG;
	new->obj_list = NULL;
	new->light_list = NULL;
	new->far_col = BLACK;
	new->cache = NULL;
	new->cache_id = -1;
	new->event = 0;
	new->first = 0;
	if (!(file_to_array(fd, new, av)))
	{
		mlx_destroy_window(new->mlx, new->win);
		return (0);
	}
	return (1);
}
