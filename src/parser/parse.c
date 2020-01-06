/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:58:30 by krutten           #+#    #+#             */
/*   Updated: 2020/01/06 19:00:04 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_scene(int *i, t_rt *specs)
{
	int		j;

	parse_vec(&specs->camera, move(i, &j, specs), specs);
	parse_vec_norm(&specs->view_dir, move(i, &j, specs), specs);
	specs->fov = ft_atof(move(i, &j, specs));
	if (specs->fov > 150 || specs->fov < 20)
		specs->fov = 90.0;
	specs->alpha = (specs->fov / 180.0) * M_PI;
	specs->abient_l = ft_atof(move(i, &j, specs));
}

void		parse_lights(int *i, t_rt *specs)
{
	int			j;
	int			len;

	j = 0;
	while (specs->input[*i][j] && specs->input[*i][j] != '(')
		j++;
	if (!(specs->input[*i][j]))
		return ;
	len = j;
	j++;
	while (specs->input[*i][j] && specs->input[*i][len] != ')')
		len++;
	len = len - j;
	if (!(specs->str = ft_strsub(specs->input[*i], j, len)))
		exit_protocol(specs, 1, "ft_strsub failed in parse_lights");
	if (!ft_strcmp(specs->str, "spherical"))
		parse_lights_s(i, specs);
	else if (!ft_strcmp(specs->str, "distant"))
		parse_lights_d(i, specs);
	else
		ft_strdel(&specs->str);
}

void		parse_lights_s(int *i, t_rt *specs)
{
	int				j;
	t_light_s		*l;
	t_obj			*new;

	new = NULL;
	ft_strdel(&specs->str);
	if (!(l = (t_light_s *)malloc(sizeof(*l))))
		exit_protocol(specs, 1, "Can't create a s_light source");
	specs->cache = l;
	specs->cache_id = 4;
	parse_vec(&l->center, move(i, &j, specs), specs);
	parse_vec_col(&l->color, move(i, &j, specs), specs);
	l->intensity = ft_abs(ft_atof(move(i, &j, specs)));
	if (!(new = new_object(l, 4)))
		exit_protocol(specs, 0, "Can't add a s_light");
	add_object(&specs->light_list, new);
}

void		parse_lights_d(int *i, t_rt *specs)
{
	int				j;
	t_light_d		*l;
	t_obj			*new;

	new = NULL;
	ft_strdel(&specs->str);
	if (!(l = (t_light_d *)malloc(sizeof(*l))))
		exit_protocol(specs, 1, "Can't create a d_light source");
	specs->cache = l;
	specs->cache_id = 5;
	parse_vec_norm(&l->direct, move(i, &j, specs), specs);
	parse_vec_col(&l->color, move(i, &j, specs), specs);
	l->intensity = ft_abs(ft_atof(move(i, &j, specs)));
	if (!(new = new_object(l, 5)))
		exit_protocol(specs, 0, "Can't add a d_light");
	add_object(&specs->light_list, new);
}

void		parse(t_rt *specs)
{
	int		i;

	i = -1;
	if (ft_strcmp(specs->input[0], "camera"))
		exit_protocol(specs, 0, "Missing camera");
	while (specs->input[++i])
	{
		if (!ft_strcmp(specs->input[i], "camera"))
			parse_scene(&i, specs);
		parse_lights(&i, specs);
		parse_objects(&i, specs);
	}
	specs->aliasing = 1;
	i = -1;
	while (++i < specs->nb_line)
		free(specs->input[i]);
	free(specs->input);
	specs->input = NULL;
}
