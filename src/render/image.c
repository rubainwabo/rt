/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:01:31 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/06 16:54:30 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	alloc_data(t_rt *specs, t_image *img)
{
	if (!(img->data = mlx_get_data_addr(img->ptr, &img->bpp,
		&img->sizeline, &img->endian)))
	{
		free(img);
		free(img->ptr);
		exit_protocol2(specs, -1, "failed to created the img string");
	}
}

t_image		*create_image(t_rt *specs, char *path, int x, int y)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
		exit_protocol2(specs, -1, "img struct malloc failed");
	if (!path)
		img->ptr = mlx_new_image(specs->mlx, x, y);
	else
		img->ptr = mlx_xpm_file_to_image(specs->mlx, path,
		&img->width, &img->height);
	if (!img->ptr)
	{
		free(img);
		exit_protocol2(specs, -1, "failed to created the img pointer");
	}
	alloc_data(specs, img);
	return (img);
}

void		init_texture(t_rt *specs)
{
	specs->textures[0] = create_image(specs, "textures/posx.xpm", 0, 0);
	specs->textures[1] = create_image(specs, "textures/negx.xpm", 0, 0);
	specs->textures[2] = create_image(specs, "textures/posy.xpm", 0, 0);
	specs->textures[3] = create_image(specs, "textures/negy.xpm", 0, 0);
	specs->textures[4] = create_image(specs, "textures/posz.xpm", 0, 0);
	specs->textures[5] = create_image(specs, "textures/negz.xpm", 0, 0);
}

void	draw_image(t_rt *specs)
{
	static int	first;

	if (first++ == 0)
		create_img_backgrd(specs);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->ui->ptr, 0, 0);
	if (specs->event == 0)
	{
		mlx_string_put(specs->mlx, specs->win, 100, 500, WHITE, "LOADING...");
		mlx_do_sync(specs->mlx);
	}
	else
		possible_events(specs);
	sub2_image(specs);
	mlx_do_sync(specs->mlx);
	if (specs->event == 0)
	{
   		destroy_img(specs, specs->img_s);
		sub_image(specs);
		mlx_do_sync(specs->mlx);
   		destroy_img(specs, specs->img_s);
		native_image(specs);
		possible_events2(specs);
	}
}

void		destroy_img(t_rt *specs, t_image *img)
{
	mlx_destroy_image(specs->mlx, img->ptr);
	free(img);
}