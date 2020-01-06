/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 21:25:58 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/06 21:39:13 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		parse_cone2(t_obj *new, int *i, t_cone *c, t_rt *specs)
{
	int		j;

	parse_vec_col(&c->surf->d_col, move(i, &j, specs), specs);
	c->surf->type = ft_atoi(move(i, &j, specs));
	set_texture(specs, move(i, &j, specs), c->surf);
	if (!(new = new_object(c, 3)))
		exit_protocol(specs, 0, "Can't add a cone");
	add_object(&specs->obj_list, new);
}

void			parse_cone(int *i, t_rt *specs)
{
	int			j;
	t_cone		*c;
	t_obj		*new;

	new = NULL;
	ft_strdel(&specs->str);
	if (!(c = (t_cone *)malloc(sizeof(*c))))
		exit_protocol(specs, 1, "Can't create an object cone");
	specs->cache = c;
	specs->cache_id = 3;
	c->surf = set_surface(specs);
	parse_vec(&c->center, move(i, &j, specs), specs);
	parse_vec_norm(&c->axis, move(i, &j, specs), specs);
	c->max = ft_atof(move(i, &j, specs));
	c->min = ft_atof(move(i, &j, specs));
	c->angle = ft_atof(move(i, &j, specs));
	c->angle = (c->angle < 20 || c->angle > 160) ? 90 : c->angle;
	c->angle = (c->angle / 2) * (M_PI / 180);
	parse_cone2(new, i, c, specs);
}

static void		parse_cylinder2(t_obj *new, int *i, t_cyl *c, t_rt *specs)
{
	int		j;

	parse_vec_col(&c->surf->d_col, move(i, &j, specs), specs);
	c->surf->type = ft_atoi(move(i, &j, specs));
	set_texture(specs, move(i, &j, specs), c->surf);
	if (!(new = new_object(c, 2)))
		exit_protocol(specs, 0, "Can't add a cylinder");
	add_object(&specs->obj_list, new);
}

void			parse_cylinder(int *i, t_rt *specs)
{
	int			j;
	t_cyl		*c;
	t_obj		*new;

	new = NULL;
	ft_strdel(&specs->str);
	if (!(c = (t_cyl *)malloc(sizeof(*c))))
		exit_protocol(specs, 1, "Can't create an object cylinder");
	specs->cache = c;
	specs->cache_id = 2;
	c->surf = set_surface(specs);
	parse_vec(&c->center, move(i, &j, specs), specs);
	parse_vec_norm(&c->axis, move(i, &j, specs), specs);
	c->max = ft_abs(ft_atof(move(i, &j, specs)));
	c->radius = ft_abs(ft_atof(move(i, &j, specs)));
	parse_cylinder2(new, i, c, specs);
}