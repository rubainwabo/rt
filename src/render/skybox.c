/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:54:16 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/08 14:33:31 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	swap_texture_skybox(t_rt *specs)
{
	int		i;

	i = -1;
	if (specs->skyboxi == 0)
		while (++i < 6)
			specs->textures[i] = specs->lake_s[i];
	else if (specs->skyboxi == 1)
		while (++i < 6)
			specs->textures[i] = specs->lake_h[i];
}

void	init_sb(t_sb *sb, t_vec3 direct)
{
	sb->max_axis = 0;
	sb->uc = 0;
	sb->vc = 0;
	sb->offset = 0;
	sb->abs_coor[0] = fabs(direct.x);
	sb->abs_coor[1] = fabs(direct.y);
	sb->abs_coor[2] = fabs(direct.z);
	sb->sign_coor[0] = direct.x > 0 ? 1 : 0;
	sb->sign_coor[1] = direct.y > 0 ? 1 : 0;
	sb->sign_coor[2] = direct.z > 0 ? 1 : 0;
}

void	hit_faces012(t_sb *sb, t_vec3 direct)
{
	if (sb->sign_coor[0] && sb->abs_coor[0] >= sb->abs_coor[1] &&
				sb->abs_coor[0] >= sb->abs_coor[2])
	{
		sb->max_axis = sb->abs_coor[0];
		sb->uc = -direct.z;
		sb->vc = -direct.y;
		sb->index = 0;
	}
	if (!sb->sign_coor[0] && sb->abs_coor[0] >= sb->abs_coor[1] &&
				sb->abs_coor[0] >= sb->abs_coor[2])
	{
		sb->max_axis = sb->abs_coor[0];
		sb->uc = direct.z;
		sb->vc = -direct.y;
		sb->index = 1;
	}
	if (sb->sign_coor[1] && sb->abs_coor[1] >= sb->abs_coor[0] &&
				sb->abs_coor[1] >= sb->abs_coor[2])
	{
		sb->max_axis = sb->abs_coor[1];
		sb->uc = direct.x;
		sb->vc = direct.z;
		sb->index = 2;
	}
}

void	hit_faces345(t_sb *sb, t_vec3 direct)
{
	if (!sb->sign_coor[1] && sb->abs_coor[1] >= sb->abs_coor[0] &&
					sb->abs_coor[1] >= sb->abs_coor[2])
	{
		sb->max_axis = sb->abs_coor[1];
		sb->uc = direct.x;
		sb->vc = direct.z;
		sb->index = 3;
	}
	if (sb->sign_coor[2] && sb->abs_coor[2] >= sb->abs_coor[0] &&
					sb->abs_coor[2] >= sb->abs_coor[1])
	{
		sb->max_axis = sb->abs_coor[2];
		sb->uc = direct.x;
		sb->vc = -direct.y;
		sb->index = 4;
	}
	if (!sb->sign_coor[2] && sb->abs_coor[2] >= sb->abs_coor[0] &&
					sb->abs_coor[2] >= sb->abs_coor[1])
	{
		sb->max_axis = sb->abs_coor[2];
		sb->uc = -direct.x;
		sb->vc = -direct.y;
		sb->index = 5;
	}
}

t_vec3	apply_texture(t_rt *specs, t_vec3 direct)
{
	t_vec3	output;
	t_sb	sb;

	init_sb(&sb, direct);
	hit_faces012(&sb, direct);
	hit_faces345(&sb, direct);
	sb.u = 0.5 * (sb.uc / sb.max_axis + 1.0);
	if (sb.u == 1.0)
		sb.u -= 1.0 / specs->textures[sb.index]->width;
	sb.v = 0.5 * (sb.vc / sb.max_axis + 1.0);
	sb.offset = (((int)(sb.u * specs->textures[sb.index]->width) + (int)(sb.v *
		specs->textures[sb.index]->height) * specs->textures[sb.index]->width));
	ft_memcpy((void *)&sb.color, (void *)specs->textures[sb.index]->data +
		(sb.offset * 4), 4);
	output.x = ((sb.color >> 16) & 0xff) / 255.0;
	output.y = ((sb.color >> 8) & 0xff) / 255.0;
	output.z = (sb.color & 0xff) / 255.0;
	return (output);
}
