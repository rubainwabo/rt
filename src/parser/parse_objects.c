/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:38:35 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/06 21:34:22 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	set_texture(specs, move(i, &j, specs), s->surf);
	if (!(new = new_object(s, 1)))
		exit_protocol(specs, 0, "Can't add a sphere");
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
	set_texture(specs, move(i, &j, specs), p->surf);
	specs->bump = ft_atoi(move(i, &j, specs));
	if (!(new = new_object(p, 0)))
		exit_protocol(specs, 0, "Can't add a plane");
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
