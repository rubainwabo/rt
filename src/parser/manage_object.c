/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:12:55 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/09 19:13:18 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*new_object(void *inf, int id)
{
	t_obj *new;

	if (!(new = (t_obj *)malloc(sizeof(*new))))
		return (NULL);
	new->obj = inf;
	new->id = id;
	new->next = NULL;
	return (new);
}

void		add_object(t_obj **list, t_obj *new)
{
	if (!*list && new)
	{
		*list = new;
		return ;
	}
	if (*list && new)
	{
		new->next = *list;
		*list = new;
	}
}

void		free_surface(int id, void *ptr)
{
	t_var	norm;

	if (id == 1)
	{
		norm.sphere = (t_sphere *)ptr;
		free(norm.sphere->surf);
	}
	if (id == 2)
	{
		norm.cyl = (t_cyl *)ptr;
		free(norm.cyl->surf);
	}
	if (id == 0)
	{
		norm.plane = (t_plane *)ptr;
		free(norm.plane->surf);
	}
	if (id == 3)
	{
		norm.cone = (t_cone *)ptr;
		free(norm.cone->surf);
	}
}

void		free_all_lists(t_rt *specs)
{
	t_obj	*temp;
	t_obj	*next;

	temp = specs->obj_list;
	while (temp)
	{
		free_surface(temp->id, temp->obj);
		free(temp->obj);
		next = temp->next;
		free(temp);
		temp = next;
	}
	specs->obj_list = NULL;
	temp = specs->light_list;
	while (temp)
	{
		free(temp->obj);
		next = temp->next;
		free(temp);
		temp = next;
	}
	specs->light_list = NULL;
}

t_surf		*set_surface(t_rt *specs)
{
	t_surf	*output;

	if (!(output = (t_surf *)malloc(sizeof(*output))))
		exit_protocol(specs, 2, "Can't create a surface");
	output->d_k = 0.8;
	output->s_exp = 20;
	output->s_k = 0.4;
	output->s_col = vec3_init(1, 1, 1);
	output->ior = 1.33;
	return (output);
}
