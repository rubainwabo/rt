/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 20:34:59 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/08 14:25:27 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** THESE FUCTIONS FREE THE SURFACE AND THE TEXTURE
*/

void	free_surf_text_sphere(t_surf *surf)
{
	if (surf->text_status == 1)
		destroy_texture(surf->texture);
	free(surf);
}

void	free_surf_text_cyl(t_surf *surf)
{
	if (surf->text_status == 1)
		destroy_texture(surf->texture);
	free(surf);
}

void	free_surf_text_cone(t_surf *surf)
{
	if (surf->text_status == 1)
		destroy_texture(surf->texture);
	free(surf);
}

void	free_surf_text_plane(t_surf *surf)
{
	if (surf->text_status == 1)
		destroy_texture(surf->texture);
	free(surf);
}

void	free_surface(int id, void *ptr)
{
	t_var	norm;

	if (id == 1)
	{
		norm.sphere = (t_sphere *)ptr;
		free(norm.sphere->surf);
	}
	if (id == 2)
	{
		norm.cyl = (t_cyl *)ptr;
		free(norm.cyl->surf);
	}
	if (id == 0)
	{
		norm.plane = (t_plane *)ptr;
		free(norm.plane->surf);
	}
	if (id == 3)
	{
		norm.cone = (t_cone *)ptr;
		free(norm.cone->surf);
	}
}
