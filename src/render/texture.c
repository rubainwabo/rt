/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:54:16 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/17 14:39:31 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	apply_texture(t_rt *specs, t_vec3 direct)
{
	t_vec3	output;
	float	abs_coor[3];
	int		sign_coor[3], index, color;
	float	maxAxis = 0, uc = 0, vc = 0, u, v;
	int offset = 0;

	abs_coor[0] = fabs(direct.x);
	abs_coor[1] = fabs(direct.y);
	abs_coor[2] = fabs(direct.z);
	sign_coor[0] = direct.x > 0 ? 1 : 0;
	sign_coor[1] = direct.y > 0 ? 1 : 0;
	sign_coor[2] = direct.z > 0 ? 1 : 0;
	if (sign_coor[0] && abs_coor[0] >= abs_coor[1] && abs_coor[0] >= abs_coor[2])
	{
		maxAxis = abs_coor[0];
		uc = -direct.z;
		vc = -direct.y;
		index = 0;
	}
	if (!sign_coor[0] && abs_coor[0] >= abs_coor[1] && abs_coor[0] >= abs_coor[2])
	{
		maxAxis = abs_coor[0];
		uc = direct.z;
		vc = -direct.y;
		index = 1;
	}
	if (sign_coor[1] && abs_coor[1] >= abs_coor[0] && abs_coor[1] >= abs_coor[2])
	{
		maxAxis = abs_coor[1];
		uc = direct.x;
		vc = direct.z;
		index = 2;
	}
	if (!sign_coor[1] && abs_coor[1] >= abs_coor[0] && abs_coor[1] >= abs_coor[2])
	{
		maxAxis = abs_coor[1];
		uc = direct.x;
		vc = direct.z;
		index = 3;
	}
	if (sign_coor[2] && abs_coor[2] >= abs_coor[0] && abs_coor[2] >= abs_coor[1])
	{
		maxAxis = abs_coor[2];
		uc = direct.x;
		vc = -direct.y;
		index = 4;
	}
	if (!sign_coor[2] && abs_coor[2] >= abs_coor[0] && abs_coor[2] >= abs_coor[1])
	{
		maxAxis = abs_coor[2];
		uc = -direct.x;
		vc = direct.y;
		index = 5;
	}
	u = 0.5 * (uc / maxAxis + 1.0);//  -1 < uc / maxaxis < 1 ||||||||| 0 < u < 1
	v = 0.5 * (vc / maxAxis + 1.0);
	offset = (((int)(u * specs->textures[index]->width) + (int)(v * specs->textures[index]->height) * specs->textures[index]->width));
	ft_memcpy((void *)&color, (void *)specs->textures[index]->data + (offset * 4), 4);
	output.x = ((color >> 16) & 0xff) / 255.0;
	output.y = ((color >> 8) & 0xff) / 255.0;
	output.z = (color & 0xff) / 255.0;
	return (output);
}