/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:38:35 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/09 16:56:54 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_sphere(int *i, t_rt *specs)
{
	int			j;
	t_sphere	*s;
	t_obj		*new;

	new = NULL;
	ft_strdel(&specs->str);
	if (!(s = (t_sphere *)malloc(sizeof(*s))))
		exit_protocol(specs, 1, "Can't create an object sphere");
	specs->cache = s;
	specs->cache_id = 1;
	s->surf = set_surface(specs);
	parse_vec(&s->center, move(i, &j, specs), specs);
	parse_vec_col(&s->surf->d_col, move(i, &j, specs), specs);
	s->radius = ft_abs(ft_atof(move(i, &j, specs)));
	s->surf->type = ft_atoi(move(i, &j, specs));
	s->surf->texture = create_image(specs, "textures/bricktexture.xpm");
	if (!(new = new_object(s, 1)))
		exit_protocol(specs, 0, "Can't add a sphere");
	add_object(&specs->obj_list, new);
}

void	parse_cylinder(int *i, t_rt *specs)
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
	parse_vec_col(&c->surf->d_col, move(i, &j, specs), specs);
	c->surf->type = ft_atoi(move(i, &j, specs));
	if (!(new = new_object(c, 2)))
		exit_protocol(specs, 0, "Can't add a cylinder");
	add_object(&specs->obj_list, new);
}

void	parse_plane(int *i, t_rt *specs)
{
	int			j;
	t_plane		*p;
	t_obj		*new;

	new = NULL;
	ft_strdel(&specs->str);
	if (!(p = (t_plane *)malloc(sizeof(*p))))
		exit_protocol(specs, 1, "Can't create an object plane");
	specs->cache = p;
	specs->cache_id = 0;
	p->surf = set_surface(specs);
	parse_vec(&p->point, move(i, &j, specs), specs);
	parse_vec_norm(&p->normal, move(i, &j, specs), specs);
	parse_vec_col(&p->surf->d_col, move(i, &j, specs), specs);
	p->surf->type = ft_atoi(move(i, &j, specs));
	p->surf->texture = create_image(specs, "textures/bricktexture.xpm");
	if (!(new = new_object(p, 0)))
		exit_protocol(specs, 0, "Can't add a plane");
	add_object(&specs->obj_list, new);
}

void	parse_cone(int *i, t_rt *specs)
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
	parse_vec_col(&c->surf->d_col, move(i, &j, specs), specs);
//	c->surf->type = dispatch_texture((move(i, &j, specs)));
	if (!(new = new_object(c, 3)))
		exit_protocol(specs, 0, "Can't add a cone");
	add_object(&specs->obj_list, new);
}

void	parse_objects(int *i, t_rt *specs)
{
	int			j;
	int			len;

	j = 0;
	while (specs->input[*i][j] && specs->input[*i][j] != '(')
		j++;
	if (!specs->input[*i][j])
		return ;
	len = j;
	j++;
	while (specs->input[*i][j] && specs->input[*i][len] != ')')
		len++;
	len = len - j;
	if (!(specs->str = ft_strsub(specs->input[*i], j, len)))
		exit_protocol(specs, 1, "ft_strsub failed in parse_objects");
	if (!ft_strcmp(specs->str, "sphere"))
		parse_sphere(i, specs);
	else if (!ft_strcmp(specs->str, "cylinder"))
		parse_cylinder(i, specs);
	else if (!ft_strcmp(specs->str, "cone"))
		parse_cone(i, specs);
	else if (!ft_strcmp(specs->str, "plane"))
		parse_plane(i, specs);
	else
		ft_strdel(&specs->str);
}
