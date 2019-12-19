/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:19:15 by krutten           #+#    #+#             */
/*   Updated: 2019/12/18 12:50:04 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			cast_ray(t_ray *ray, t_rt *specs, t_ray *original)
{
	t_ray		refl;
	t_ray		refr;

	ray->t = FAR;
	loop_ray_over_objects(ray, specs);
	if (ray->t < FAR && ray->surf->type == 1 && ray->depth < MAX_DEPTH)
	{
		reflected_ray(ray, &refl);
		cast_ray(&refl, specs, original);
		refracted_ray(ray, &refr);
		cast_ray(&refr, specs, original);
		fresnel_blend(&refl, &refr, ray);
		return (colour_mask(0.8, ray->surf->d_col, ray));
	}
	else if (ray->t < FAR && ray->surf->type == 2 && ray->depth < MAX_DEPTH)
	{
		reflected_ray(ray, &refl);
		cast_ray(&refl, specs, original);
		ray->colour = refl.colour;
		return (colour_mask(0.8, ray->surf->d_col, ray)); //0.8 % reflec
	}
	else if (ray->t < FAR && ray->depth < MAX_DEPTH)
		return (diffuse_prot(ray, specs, original));
	ray->colour = vec3_init(0, 0, 0);
	return (1);
}

void		spawn_ray(int x, int y, t_rt *specs)
{
	t_ray	ray;
	t_surf	surf;

	ray.surf = &surf;
	ray.origin = specs->camera;
	ray.direct = pixel_to_world((float)x / specs->w_img, (float)y / specs->h_img, specs);
	ray.depth = 0;
	ray.ior = 1.0;
	ray.nohit = 0;
	ray.direct = normalise(ray.direct);
	ray.nohit = cast_ray(&ray, specs, &ray);
	if (ray.nohit == 0)
		shading(&ray, specs, x, y);
	else
		shading_far(specs, x, y);
}

void		*pixel_loop(void *data)
{
	t_thread	*d;
	int			x;
	int			y;

	d = (t_thread *)data;
	y = d->y_start - 1;
	while (++y < d->y_end)
	{
		x = -1;
		while (++x < d->specs->w_img)
			spawn_ray(x, y, d->specs);
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_rt		specs;
	int			fd;

	if (ac != 2)
		return (ft_error("Usage: ./rtv1 scenefile"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("");
		return (0);
	}
	if (!init_rt_struct(fd, &specs, av))
		return (ft_error("Failed to read input file"));
	parse(&specs);
	if (!draw_image(&specs))
		exit_protocol2(&specs, 1, "Can't create the image");
	mlx_key_hook(specs.win, deal_key, &specs);
	mlx_loop(specs.mlx);
	return (0);
}
