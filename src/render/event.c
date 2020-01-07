/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:05:20 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/07 20:53:55 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	deal_key_mov(int key, t_rt *specs)
{
	if (key == RIGHT)
	{
		specs->camera.x -= 1.25;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == LEFT)
	{
		specs->camera.x += 1.25;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == UP)
	{
		specs->camera.y -= 1.25;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == DOWN)
	{
		specs->camera.y += 1.25;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
}

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
	if (key == T)
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
	if (key == ESC)
		exit_protocol2(specs, 19, "exit with code 0");
	deal_key_filter(key, specs);
	return (0);
}

int		move_cam(int button, int x, int y, t_rt *specs)
{
	float		xm;
	float		ym;

	if (button == LEFTCLICK && specs->event == 1)
	{
		specs->first = 0;
		if (x - POS_X < 0)
			return (0);
		xm = ((2.0 * (double)(x - POS_X) / W_IMG) - 1.0) *
		specs->alpha * specs->aspect;
		ym = (1.0 - (2.0 * (double)y / H_IMG)) * specs->alpha;
		specs->view_dir.x = xm;
		specs->view_dir.y = ym;
		specs->view_dir.z = -1.0;
		specs->view_dir = normalise(specs->view_dir);
		specs->view_dir = vector_matrix_multiply(specs->view_dir,
		specs->view_rot);
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	return (0);
}
