/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 19:18:28 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/06 21:34:46 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_texture(t_rt *specs, char *str, t_surf *surf)
{
	if (!ft_strncmp(str, "brick", 5))
	{
		surf->text = 1;
		surf->texture = create_image(specs, "textures/bricktexture.xpm", 1, 0);
	}
	else if (!ft_strncmp(str, "lake", 4))
	{
		surf->text = 1;
		surf->texture = create_image(specs, "textures/bricktexture.xpm", 1, 0);
	}
	else if (!ft_strncmp(str, "none", 4))
		surf->text = 0;
}