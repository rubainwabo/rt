/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:36:55 by krutten           #+#    #+#             */
/*   Updated: 2019/12/09 19:58:14 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		intersection_vec3(t_ray *ray)
{
	ray->hitpoint.x = ray->t * ray->direct.x + ray->origin.x;
	ray->hitpoint.y = ray->t * ray->direct.y + ray->origin.y;
	ray->hitpoint.z = ray->t * ray->direct.z + ray->origin.z;
}

t_vec3		normalise(t_vec3 v1)
{
	float	length;
	t_vec3	norm_vec;

	length = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	if (length == 0)
		return (vec3_init(0, 0, -1));
	norm_vec.x = v1.x / length;
	norm_vec.y = v1.y / length;
	norm_vec.z = v1.z / length;
	return (norm_vec);
}
