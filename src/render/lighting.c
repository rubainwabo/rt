/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:46:50 by krutten           #+#    #+#             */
/*   Updated: 2020/01/07 21:22:56 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	diffuse_light(double dot, t_vec3 lcolor, t_vec3 dcolor, t_ray *ray)
{
	ray->colour.x += dot * lcolor.x * dcolor.x;
	ray->colour.y += dot * lcolor.y * dcolor.y;
	ray->colour.z += dot * lcolor.z * dcolor.z;
}

void	specular_light(double dot, t_vec3 lcolor, t_vec3 scolor, t_ray *ray)
{
	ray->colour.x += dot * lcolor.x * scolor.x;
	ray->colour.y += dot * lcolor.y * scolor.y;
	ray->colour.z += dot * lcolor.z * scolor.z;
}

void	lighting_distant(t_ray *ray, t_rt *specs, t_ray *shadow_ray, t_obj *l)
{
	t_light_d	*light;
	double		spdot;

	light = (t_light_d *)l->obj;
	shadow_ray->direct = light->direct;
	shadow_ray->t = FAR;
	loop_shadow_ray_over_objects(shadow_ray, specs);
	if (shadow_ray->t == FAR)
	{
		diffuse_light(ray->surf->d_k * ft_max(vec3_dot(ray->hitnormal,
					shadow_ray->direct), 0)
					* light->intensity, light->color, ray->texcol, ray);
		if ((spdot = vec3_dot(ray->direct,
		reflect(ray->hitnormal, shadow_ray->direct))) > 0.7)
			specular_light(ray->surf->s_k * pow(spdot, ray->surf->s_exp) *
			light->intensity, light->color, ray->surf->s_col, ray);
	}
}

void	lighting_spherical(t_ray *ray, t_rt *specs, t_ray *shadow_ray, t_obj *l)
{
	t_light_s	*light;
	double		dist;
	double		spdot;

	light = (t_light_s *)l->obj;
	shadow_ray->direct = vec3_add(light->center, ray->hitpoint, '-');
	shadow_ray->t = sqrt(vec3_dot(shadow_ray->direct, shadow_ray->direct));
	shadow_ray->direct = normalise(shadow_ray->direct);
	dist = shadow_ray->t;
	specs->x = specs->x;
	loop_shadow_ray_over_objects(shadow_ray, specs);
	if (shadow_ray->t == dist)
	{
		diffuse_light(ray->surf->d_k * ft_max(vec3_dot(ray->hitnormal,
			shadow_ray->direct), 0) * light->intensity / (dist * dist),
			light->color, ray->texcol, ray);
		if ((spdot = vec3_dot(ray->direct, reflect(ray->hitnormal,
		shadow_ray->direct))) > 0.7)
			specular_light(ray->surf->s_k * pow(spdot, ray->surf->s_exp)
			* light->intensity / (dist * dist),
			light->color, ray->surf->s_col, ray);
	}
}

void	lighting(t_ray *ray, t_rt *specs)
{
	t_ray	shadow_ray;
	t_obj	*l;

	l = specs->light_list;
	shadow_ray.origin = ray->hitpoint;
	if (ray->surf->text == 0)
		ray->texcol = ray->surf->d_col;
	ray->colour = vec3_scale(ray->texcol, specs->abient_l, '*');
	while (l)
	{
		if (l->id == 5)
			lighting_distant(ray, specs, &shadow_ray, l);
		if (l->id == 4)
			lighting_spherical(ray, specs, &shadow_ray, l);
		l = l->next;
	}
}
