/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:54:39 by krutten           #+#    #+#             */
/*   Updated: 2019/11/05 14:19:20 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rtv1.h"

t_vec3		reflect(t_vec3 norm, t_vec3 inci)
{
	return (vec3_add(inci, vec3_scale(vec3_scale(norm, vec3_dot(norm, inci),
		'*'), 2, '*'), '-'));
}

void		reflected_ray(t_ray *ray, t_ray *refl)
{
	refl->origin = ray->hitpoint;
	refl->depth = ray->depth + 1;
	refl->ior = ray->ior;
	refl->direct = reflect(ray->hitnormal, ray->direct);
}

/*
** Formula for refraction is Ref_dir = ηI+(ηc1−c2)N
** n1n2 = η. Precomputed for time saving
** c1 = cosi. Also precomputed
** c2 = sqrt(1 − (n1n2)^2 * sin^2(θ1))
*/

void		refracted_ray(t_ray *ray, t_ray *refr)
{
	double		n1n2;
	double		cosi;

	n1n2 = ray->ior / ray->surf->ior;
	cosi = vec3_dot(ray->direct, ray->hitnormal);
	cosi = (cosi < 0) ? -cosi : cosi;
	refr->origin = ray->hitpoint;
	refr->depth = ray->depth + 1;
	refr->direct = vec3_add(vec3_scale(ray->direct, n1n2, '*'),
	vec3_scale(ray->hitnormal, (n1n2 * cosi - pow(1 - ((n1n2 * n1n2)
				* (1 - cosi * cosi)), 0.5)), '*'), '+');
	refr->direct = normalise(refr->direct);
	refr->ior = ray->surf->ior;
}

void		fresnel_blend(t_ray *refl, t_ray *refr, t_ray *ray)
{
	double		n[9];

	n[0] = vec3_dot(ray->direct, ray->hitnormal);
	n[1] = ray->ior;
	n[2] = ray->surf->ior;
	if (n[0] > 0)
	{
		n[3] = n[1];
		n[1] = n[2];
		n[2] = n[3];
	}
	n[4] = n[1] / n[2] * sqrtf(ft_max(1 - (n[0] * n[0]), 0));
	if (n[4] > 1.001 || n[4] < -1.001)
	{
		ray->colour = refl->colour;
		return ;
	}
	n[5] = sqrtf(1 - (n[4] * n[4]));
	n[0] = (n[0] > 0 ? n[0] : -n[0]);
	n[6] = ((n[2] * n[0]) - (n[1] * n[5])) / ((n[2] * n[0]) + (n[1] * n[5]));
	n[7] = ((n[1] * n[0]) - (n[2] * n[5])) / ((n[1] * n[0]) + (n[2] * n[5]));
	n[8] = (n[7] * n[7] + n[6] * n[6]) / 2;
	ray->colour.x = refl->colour.x * n[8] + refr->colour.x * (1 - n[8]);
	ray->colour.y = refl->colour.y * n[8] + refr->colour.y * (1 - n[8]);
	ray->colour.z = refl->colour.z * n[8] + refr->colour.z * (1 - n[8]);
}
