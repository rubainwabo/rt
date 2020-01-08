/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 22:47:27 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/08 17:11:40 by rkamegne         ###   ########.fr       */
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
	if (key == V)
	{
		specs->texmove[0] -= 1;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == NUM2)
	{
		specs->camera.z += 1.25;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
}

void	deal_key_mov2(int key, t_rt *specs)
{
	if (key == X)
	{
		specs->texstretch *= 1.1;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == C)
	{
		specs->texstretch /= 1.1;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == B)
	{
		specs->texmove[0] += 1;
		destroy_img(specs, specs->img_s);
		draw_image(specs);
	}
	if (key == NUM8)
	{
		specs->camera.z -= 1.25;
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
