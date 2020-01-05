/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:05:20 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/19 23:00:05 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	deal_key_mov(int key, t_rt *specs)
{
	if (key == K_AR_R)
	{
		specs->camera.x -= 1.25;
		draw_image(specs);
	}
	if (key == K_AR_L)
	{
		specs->camera.x += 1.25;
		draw_image(specs);
	}
	if (key == K_AR_U)
	{
		specs->camera.y -= 1.25;
		draw_image(specs);
	}
	if (key == K_AR_D)
	{
		specs->camera.y += 1.25;
		draw_image(specs);
	}
}

void	deal_key_filter(int key, t_rt *specs)
{
	if (key == K_A)
	{
		apply_grayscale(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == K_D)
	{
		apply_sepia(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == K_F)
	{
		apply_blue(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == K_G)
	{
		reverse_chan(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
	if (key == K_H)
	{
		apply_purple(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
	}
}

int			deal_key(int key, t_rt *specs)
{
	if (specs->event == EVENT)
		deal_key_mov(key, specs);
	if (key == K_SP)
	{
		specs->event = !specs->event;
		draw_image(specs);
	}
	if (key == K_S)
		save_file(specs);
	if (key == K_L)
	{
		draw_backgrd(specs);
		mlx_string_put(specs->mlx, specs->win, 100, 300, WHITE, "LOADING...");
   		destroy_img(specs, specs->img_s);
		super_image(specs);
		possible_events2(specs);
		specs->event = NO_EVENT;
	}
	if (key == K_ESC)
		exit_protocol2(specs, 19, "exit with code 0");
	deal_key_filter(key, specs);	
	return (0);
}

int 	move_cam(int button, int x, int y, t_rt *specs)
{
	float		xm;
	float		ym;

	if (button == M_CLK_L && specs->event == EVENT)
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
		draw_image(specs);
	}
	return (0);
}