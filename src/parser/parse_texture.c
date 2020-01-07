/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 19:18:28 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/07 23:18:55 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	alloc_data(t_rt *specs, t_image *img, t_surf *surf, int p)
{
	if (!(img->data = mlx_get_data_addr(img->ptr, &img->bpp,
		&img->sizeline, &img->endian)))
	{
		free(img);
		free(img->ptr);
		free(surf);
		exit_protocol(specs, p, "Can't load texture");
	}
}

/*
** this function will create the texture image and manage the memory in
** failing case
** p = where the malloc failed
*/

t_image		*create_texture_image(t_rt *specs, char *path, t_surf *surf, int p)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
		exit(1);
	if (!path || !(img->ptr = mlx_xpm_file_to_image(specs->mlx, path,
		&img->width, &img->height)))
	{
		free(img);
		free(surf);
		exit_protocol(specs, p, "Can't load texture");
	}
	alloc_data(specs, img, surf, p);
	return (img);
}

void		set_texture(t_rt *specs, char *str, t_surf *surf)
{
	if (!ft_strncmp(str, "brick", 5))
	{
		surf->text = 1;
		surf->texture = create_texture_image(specs,
									"textures/bricktexture.xpm", surf, 2);
	}
	else if (!ft_strncmp(str, "lake", 4))
	{
		surf->text = 1;
		surf->texture = create_texture_image(specs,
									"textures/bricktexture.xpm", surf, 2);
	}
	else if (!ft_strncmp(str, "wood", 4))
	{
		surf->text = 1;
		surf->texture = create_texture_image(specs,
									"textures/wood.xpm", surf, 2);
	}
}

void		destroy_texture(t_image *img)
{
	free(img->data);
	free(img->ptr);
	free(img);
}
