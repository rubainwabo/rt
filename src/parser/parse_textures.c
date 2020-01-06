/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:09:40 by krutten           #+#    #+#             */
/*   Updated: 2019/12/18 16:10:03 by krutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	dispatch_texture(char *input_str, t_rt *specs, t_surf *surf)
{
	if (!ft_strncmp(input_str, "brick", 5))//load texture into surf->texture
		surf->texture = create_image(specs,
		"textures/Lakeside/bricktexture.xpm");
	else if (!ft_strncmp(input_str, "lake", 4))
		surf->texture = create_image(specs, "textures/Lakeside/posx.xpm");
	else if (!ft_strncmp(input_str, "marble", 6))
}