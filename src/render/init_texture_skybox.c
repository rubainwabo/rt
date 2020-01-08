/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_skybox.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 22:53:44 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/08 00:56:38 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				free_texture_arr(t_rt *specs, int p)
{
	int		i;

	i = -1;
	while (++i < p)
		destroy_texture(specs->textures[i]);
}

static void			alloc_data_sky(t_rt *specs, t_image *img, int p)
{
	if (!(img->data = mlx_get_data_addr(img->ptr, &img->bpp,
		&img->sizeline, &img->endian)))
	{
		free(img);
		free(img->ptr);
		free_texture_arr(specs, p);
		mlx_destroy_window(specs->mlx, specs->win);
		ft_putendl_fd("failed to init skybox textures", 2);
		exit(1);
	}
}

/*
** this function will create the texture image and manage the memory in
** failing case
*/

static t_image		*create_texture_skybox(t_rt *specs, char *path, int p)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
	{
		free_texture_arr(specs, p);
		mlx_destroy_window(specs->mlx, specs->win);
		ft_putendl_fd("failed to init skybox textures", 2);
		exit(1);
	}
	if (!path || !(img->ptr = mlx_xpm_file_to_image(specs->mlx, path,
		&img->width, &img->height)))
	{
		free(img);
		free_texture_arr(specs, p);
		mlx_destroy_window(specs->mlx, specs->win);
		ft_putendl_fd("failed to init skybox textures", 2);
		exit(1);
	}
	alloc_data_sky(specs, img, p);
	return (img);
}

static void			init_texture2(t_rt *specs)
{
	specs->textures[0] = create_texture_skybox(specs,
					"textures/LakeHigh/posx.xpm", 0);
	specs->textures[1] = create_texture_skybox(specs,
					"textures/LakeHigh/negx.xpm", 1);
	specs->textures[2] = create_texture_skybox(specs,
					"textures/LakeHigh/posy.xpm", 2);
	specs->textures[3] = create_texture_skybox(specs,
					"textures/LakeHigh/negy.xpm", 3);
	specs->textures[4] = create_texture_skybox(specs,
					"textures/LakeHigh/posz.xpm", 4);
	specs->textures[5] = create_texture_skybox(specs,
					"textures/LakeHigh/negz.xpm", 5);
}

void				init_texture(t_rt *specs)
{

	if (specs->skyboxi == 0)
	{
		specs->textures[0] = create_texture_skybox(specs,
					"textures/LakeSide/posx.xpm", 0);
		specs->textures[1] = create_texture_skybox(specs,
					"textures/LakeSide/negx.xpm", 1);
		specs->textures[2] = create_texture_skybox(specs,
					"textures/LakeSide/posy.xpm", 2);
		specs->textures[3] = create_texture_skybox(specs,
					"textures/LakeSide/negy.xpm", 3);
		specs->textures[4] = create_texture_skybox(specs,
					"textures/LakeSide/posz.xpm", 4);
		specs->textures[5] = create_texture_skybox(specs,
					"textures/LakeSide/negz.xpm", 5);
	}
	else if (specs->skyboxi == 1)
		init_texture2(specs);
}
