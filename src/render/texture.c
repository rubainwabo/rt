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

#include "rtv1.h"

t_vec3	apply_texture(t_rt *specs, t_vec3 direct)
{
	t_vec3	output;
	float	abs_coor[3];
	int		sign_coor[3], index, color;
	float	maxAxis, uc, vc, u, v;
	int offset = 0;

	abs_coor[0] = fabs(direct.x);
	abs_coor[1] = fabs(direct.y);
	abs_coor[2] = fabs(direct.z);
	sign_coor[0] = direct.x > 0 ? 1 : 0;
	sign_coor[1] = direct.y > 0 ? 1 : 0;
	sign_coor[2] = direct.z > 0 ? 1 : 0;
	if (sign_coor[0] && abs_coor[0] >= abs_coor[1] && abs_coor[0] >= abs_coor[2])//to solve seams, try capping uc
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
		vc = -direct.y;
		index = 5;
	}
	u = 0.5 * (uc / maxAxis + 1.0);//  -1 < uc / maxaxis < 1 ||||||||| 0 < u < 1 // or better yet capping u and v
	v = 0.5 * (vc / maxAxis + 1.0);
	offset = (((int)(u * specs->textures[index]->width) + (int)(v * specs->textures[index]->height) * specs->textures[index]->width));
	ft_memcpy((void *)&color, (void *)specs->textures[index]->data + (offset * 4), 4);
	output.x = ((color >> 16) & 0xff) / 255.0;
	output.y = ((color >> 8) & 0xff) / 255.0;
	output.z = (color & 0xff) / 255.0;
	return (output);
}

//Generate u, v basis vectors for the plane. Based on normal vector (nx, ny, nz). First try (-ny, nx, 0), check if that is 0, 0, 0, then just do 1 0 0 lmao.
//perform u, v texture lookup. This means 1 pixel per 1 square world surface. Thats likely ugly, so do 10 * 10 instead. This will mean the pattern repeat every width/10 units, and height/10 units
//uv lookup for different objects will be a bit more complex

int		uv_plane_compute(t_plane *p, t_vec3 coord, t_ray *ray)
{
	t_vec3	u_base;
	t_vec3	v_base;
	double	u;
	double	v;

	if (p->normal.x || p->normal.y)
		u_base = vec3_init(-p->normal.y, p->normal.x, 0);
	else
		u_base = vec3_init(1, 0, 0);
	u_base = normalise(u_base);
	v_base = vec3_cross(p->normal, u_base);
	v_base = normalise(v_base);
	u = vec3_dot(u_base, coord);
	u = fabs(u);
	u = fmod(u * 40, ray->surf->texture->width);//u is always between 0 and width, with 10 pixels per world unit
	v = vec3_dot(v_base, coord);
	v = fabs(v);
	v = fmod(v * 40, ray->surf->texture->height);//v is always between 0 and height, with 10 pixels per world unit
	return ((int)(u) + (int)(v) * ray->surf->texture->width);
}

t_vec3	plane_texturing(t_plane *p, t_ray *ray)
{
	int		offset;
	int		color;
	t_vec3	output;

	//construct basis vectors of plane.
	offset = uv_plane_compute(p, vec3_add(ray->hitpoint, p->point, '-'), ray);
	ft_memcpy(&color, &ray->surf->texture->data[4 * offset], 4);
	output.x = ((color >> 16) & 0xff) / 255.0;
	output.y = ((color >> 8) & 0xff) / 255.0;
	output.z = (color & 0xff) / 255.0;
	return (output);
}

int		uv_sphere_compute(t_vec3 coord, t_ray *ray)
{
	double	theta;
	double	phi;
	double	u;
	double	v;

	//from displace vector hitpoint - center, decompose displacement into x, y, z. I think normalising is sufficient to remove r from the equation
	//x=cos(ϕ)cos(θ)
	//y=sin(ϕ)cos(θ)
	//z=sin(θ)
	//thus, in 2d spherical coord theta, phi
	//theta = asin(z)											NORMALLY RESTRICTED TO [-90 +90]
	//phi = atan(y/x) because y/x = tan(phi), atan(y/x) = phi	NORMALLY RESTRICTED TO [-180 +180]
	//to normalise to u,v [0,1], perform
	//u = (theta+ pi/2) / pi
	//v = (phi + pi) / 2pi
//	printf("displacement vector normalised of sphere intersects [%f,\t%f,\t%f]\n", coord.x, coord.y, coord.z);
	theta = atan(coord.z / coord.x);
	phi = asin(coord.y);
	u = (theta + M_PI / 2.0) / M_PI;
	v = (phi + M_PI) / (2.0 * M_PI);
	printf("returning offset %d\n", (int)(u) + (int)(v) * ray->surf->texture->width);
	return ((int)(u * ray->surf->texture->width) + (int)(v * ray->surf->texture->height) * ray->surf->texture->width);
}

t_vec3	sphere_texturing(t_sphere *s, t_ray *ray)
{
	int		offset;
	int		color;
	t_vec3	output;

	//spherical theta phi coords of sphere intersected converted to u, v and subsequently to the lookup index in the texture array
	offset = uv_sphere_compute(normalise(vec3_add(ray->hitpoint, s->center, '-')), ray);
	ft_memcpy(&color, &ray->surf->texture->data[4 * offset], 4);
	output.x = ((color >> 16) & 0xff) / 255.0;
	output.y = ((color >> 8) & 0xff) / 255.0;
	output.z = (color & 0xff) / 255.0;
	return (output);
}
