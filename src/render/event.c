/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:05:20 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/08 16:29:59 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
