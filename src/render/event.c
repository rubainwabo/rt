/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:05:20 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/06 15:56:13 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	deal_key_mov3(int key, t_rt *specs)
{
	if (key == N)
	{
		specs->texmove[1] += 1;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == M)
	{
		specs->texmove[1] -= 1;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
}

void	deal_key_mov2(int key, t_rt *specs)
{
	if (key == X)
	{
		specs->texstretch *=1.1;
		printf("texstretch%f\n", specs->texstretch);
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == C)
	{
		specs->texstretch /= 1.1;
		printf("texstretch%f\n", specs->texstretch);
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == B)
	{
		specs->texmove[0] += 1;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == V)
	{
		specs->texmove[0] -= 1;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	deal_key_mov3(key, specs);
}

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
	deal_key_mov2(key, specs);
}

void	deal_key_filter(int key, t_rt *specs)
{
	if (key == A)
	{
		apply_grayscale(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == D)
	{
		apply_sepia(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == F)
	{
		apply_blue(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == G)
	{
		reverse_chan(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == H)
	{
		apply_purple(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
}

int			deal_key(int key, t_rt *specs)
{
	if (specs->event == 1)
		deal_key_mov(key, specs);
	if (key == SPACE)
	{
		specs->event = !specs->event;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == S)
		save_file(specs);
	if (key == L && specs->aliasing == 1)
	{
   		destroy_img(specs, specs->img_s);
		super_image(specs);
		possible_events3(specs);
		specs->event = 0;
		specs->aliasing = 0;
	}
	if (key == T)
	{
		specs->skyboxi = (specs->skyboxi + 1) % 2;
		init_texture(specs);
		draw_image(specs);
	}
	if (key == ESC)
		exit_protocol2(specs, 19, "exit with code 0");
	deal_key_filter(key, specs);	
	return (0);
}

int 	move_cam(int button, int x, int y, t_rt *specs)
{
	float		xm;
	float		ym;

	if (button == LEFTCLICK && specs->event == 1)
	{
		specs->first = 0;
		if (x - POS_X < 0)
			return (0);
		xm = ((2.0 * (double)(x - POS_X) / W_IMG) - 1.0) * specs->alpha * specs->aspect;
		ym = (1.0 - (2.0 * (double)y / H_IMG)) * specs->alpha;
		specs->view_dir.x = xm;
		specs->view_dir.y = ym;
		specs->view_dir.z = -1.0;
		specs->view_dir = normalise(specs->view_dir);
		specs->view_dir = vector_matrix_multiply(specs->view_dir, specs->view_rot);
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	return (0);
}