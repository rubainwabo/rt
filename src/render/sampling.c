/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:21:50 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/07 18:43:19 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	super_image(t_rt *specs)
{
	mlx_put_image_to_window(specs->mlx, specs->win, specs->ui->ptr, 0, 0);
	mlx_string_put(specs->mlx, specs->win, 100, 500, WHITE, "LOADING...");
	mlx_do_sync(specs->mlx);
	specs->w_img = W_IMG * 2;
	specs->h_img = H_IMG * 2;
	specs->img = create_image(specs, 1, specs->w_img, specs->h_img);
	specs->img_s = create_image(specs, 2, W_IMG, H_IMG);
	launch_threads(specs, THREAD_COUNT);
	super_sampling(specs);
	destroy_img(specs, specs->img);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr,
														POS_X, POS_Y);
}

void	sub_image(t_rt *specs)
{
	specs->w_img = W_IMG / 2;
	specs->h_img = H_IMG / 2;
	specs->img = create_image(specs, 1, specs->w_img, specs->h_img);
	specs->img_s = create_image(specs, 2, W_IMG, H_IMG);
	launch_threads(specs, THREAD_COUNT);
	sub_sampling(specs);
	destroy_img(specs, specs->img);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr,
														POS_X, POS_Y);
}

void	sub2_image(t_rt *specs)
{
	specs->w_img = W_IMG / 4;
	specs->h_img = H_IMG / 4;
	specs->img = create_image(specs, 1, specs->w_img, specs->h_img);
	specs->img_s = create_image(specs, 2, W_IMG, H_IMG);
	launch_threads(specs, THREAD_COUNT);
	sub2_sampling(specs);
	destroy_img(specs, specs->img);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr,
														POS_X, POS_Y);
}

void	native_image(t_rt *specs)
{
	int		i;
	int		size;

	i = -1;
	size = W_IMG * H_IMG * 4;
	specs->w_img = W_IMG;
	specs->h_img = H_IMG;
	specs->img = create_image(specs, 1, specs->w_img, specs->h_img);
	specs->img_s = create_image(specs, 2, W_IMG, H_IMG);
	launch_threads(specs, THREAD_COUNT);
	while (++i < size)
		specs->img_s->data[i] = specs->img->data[i];
	destroy_img(specs, specs->img);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr,
														POS_X, POS_Y);
}
