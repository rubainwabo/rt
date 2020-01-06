/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:29:57 by krutten           #+#    #+#             */
/*   Updated: 2020/01/06 20:02:32 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	bump_map(t_ray *ray, t_plane *spec, double bumpwidth, t_vec3 parallel)
{
	double	dist;
	t_vec3	temp;
	t_vec3	temp2;
	t_mat3	rot;
//bump map will tilt the normal between -30 degrees and +30 degrees depending on the distance to the parallel vector
//the direction in which it tilts is inside of the plane which the parallel vector is normal to
//in other words, the axis of rotation is the parallel vector
//to massively reduce computational overhead, precompute the maximum tilt both ways and interpolate non linearly, but along a sine graph
//this sounds a bit complicated since it would require storing 2 more vec3 variables per plane, and straight out wouldnt work for a non-plane object
//instead, perform axis angle rotation with axis parallel and angle -30 at dist 0, 30 at dist bumpwidth / 2, -30 at dist bumpwidth
	temp = vec3_add(ray->hitpoint, spec->point , '-');//vector from point to hitpoint
	temp2 = vec3_scale(parallel, vec3_dot(temp, parallel), '*');//component of above vector parallel to vec3 parallel
	temp = vec3_add(temp, temp2, '-');//original vector minus parallel vector results in perpendicular vector
	dist = pow(vec3_dot(temp, temp), 0.5);//dot product of vector with itself is length of vector
//	printf("%f\n", dist);
//now to make the perturbation nonlinearly vary between -30 and +30 per unit of bumpwidth
//angle is dist/bumpwidth * 2PI
	rot = mat3_unit();
	rot_from_base2((cos(fmod(dist / bumpwidth, 1.0) * 2 * 3.1415)) * (3.1415 / 6), &parallel, &rot);
	ray->hitnormal = vector_matrix_multiply(ray->hitnormal, rot);
}// length of (a - p) - ((a - p) . n)n

void	normal_towards_cam(t_ray *ray)
{
	double	len1;
	double	len2;
	t_vec3	tmp;

	tmp = vec3_add(ray->origin, ray->hitpoint, '-');
	len1 = sqrt(vec3_dot(tmp, tmp));
	tmp = vec3_scale(ray->hitnormal, 0.05, '*');
	tmp = vec3_add(ray->hitpoint, tmp, '+');
	tmp = vec3_add(ray->origin, tmp, '-');
	len2 = sqrt(vec3_dot(tmp, tmp));
	if (len2 > len1)
		ray->hitnormal = vec3_scale(ray->hitnormal, -1.0, '*');
}

int		plane_intersect(t_rt *spec, t_ray *ray, void *hit_object)
{
	t_vec3	oc;
	double	t;
	t_plane	*p;

	(void)spec;
	p = (t_plane *)hit_object;
	oc = vec3_add(ray->origin, p->point, '-');
	if (vec3_dot(ray->direct, p->normal) == 0)
		return (0);
	t = (vec3_dot(oc, p->normal) * (-1))
		/ vec3_dot(ray->direct, p->normal);
	if (t < ray->t && t > NEAR)
	{
		ray->t = t;
		ray->surf = p->surf;
		intersection_vec3(ray);
		ray->hitnormal = p->normal;
		oc = vec3_init(0, -ray->hitnormal.z, ray->hitnormal.y);
		if (vec3_dot(ray->hitnormal, vec3_init(1, 0, 0)) > 0.999)
			oc = vec3_init(-ray->hitnormal.y, ray->hitnormal.x, 0);
		if (spec->bump == 1)
			bump_map(ray, p, 2, oc);
		//we need to define a direction along which to bump map the surface
		//for every plane except the one with normal 1, 0, 0 we can just choose 0, -nz, ny
		//for plane with normal 1, 0, 0, choose -ny, nx, 0
		if (p->surf->text == 1)
			ray->surf->d_col = plane_texturing(p, ray);
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}
