/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:05:20 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/08 14:12:07 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	turn_on_off_textures(t_rt *specs)
{
	t_plane		*p;
	t_sphere	*s;
	t_obj		*list;

	list = specs->obj_list;
	while (list)
	{
		if (list->id == 0)
		{
			p = (t_plane *)list->obj;
			if (p->surf->text && p->surf->text_status)
				p->surf->text = 0;
			else if (!p->surf->text && p->surf->text_status)
				p->surf->text = 1;
		}
		if (list->id == 1)
		{
			s = (t_sphere *)list->obj;
			if (s->surf->text && s->surf->text_status)
				s->surf->text = 0;
			else if (!s->surf->text && s->surf->text_status)
				s->surf->text = 1;
		}
		list = list->next;
	}
}

void	deal_key_filter2(int key, t_rt *specs)
{
	if (key == G)
	{
		reverse_chan(specs);
		mlx_put_image_to_window(specs->mlx,
		specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == P)
	{
		apply_red(specs);
		mlx_put_image_to_window(specs->mlx,
		specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == U)
	{
		turn_on_off_textures(specs);
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
}

void	deal_key_filter(int key, t_rt *specs)
{
	if (key == A)
	{
		apply_grayscale(specs);
		mlx_put_image_to_window(specs->mlx,
		specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == D)
	{
		apply_sepia(specs);
		mlx_put_image_to_window(specs->mlx,
		specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == O)
	{
		apply_blue(specs);
		mlx_put_image_to_window(specs->mlx,
		specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	deal_key_filter2(key, specs);
}

void	deal_key2(int key, t_rt *specs)
{
	if (key == T)
	{
		specs->skyboxi = !specs->skyboxi;
		destroy_img(specs, specs->img_s);
		swap_texture_skybox(specs);
		draw_image(specs);
	}
	if (key == ESC)
		exit_protocol2(specs, 19, "exit with code 0");
	deal_key_filter(key, specs);
}

int		deal_key(int key, t_rt *specs)
{
	if (specs->event == 1)
		deal_key_mov(key, specs);
	if (key == SPACE)
	{
		specs->event = !specs->event;
		specs->aliasing = 1;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == S)
		save_file(specs);
	if (key == L && specs->aliasing == 1)
	{
		destroy_img(specs, specs->img_s);
		super_image(specs);
		possible_events_aliasing(specs);
		specs->event = 0;
		specs->aliasing = 0;
	}
	deal_key2(key, specs);
	return (0);
}
