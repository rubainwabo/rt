/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:01:31 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/07 20:39:41 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** create_image with 1 destroys the ui allocated only
**                   2 destroys the first string allocated and the ui
** 19 because the input->array is already freed in parse
*/

static void		call_right_protocol(t_rt *specs, int lvl)
{
	if (lvl == 0)
		exit_protocol(specs, 19, "Can't create the background image");
	else if (lvl == 1)
	{
		destroy_img(specs, specs->ui);
		exit_protocol(specs, 19, "Can't create the first sample image");
	}
	else if (lvl == 2)
	{
		destroy_img(specs, specs->img);
		destroy_img(specs, specs->ui);
		exit_protocol(specs, 19, "Can't create the second sample image");
	}
}

static void		alloc_data(t_rt *specs, int lvl, t_image *img)
{
	if (!(img->data = mlx_get_data_addr(img->ptr, &img->bpp,
		&img->sizeline, &img->endian)))
	{
		free(img);
		free(img->ptr);
		call_right_protocol(specs, lvl);
	}
}

/*
** lvl is where an error occurs
*/

t_image			*create_image(t_rt *specs, int lvl, int x, int y)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
		call_right_protocol(specs, lvl);
	if (!(img->ptr = mlx_new_image(specs->mlx, x, y)))
	{
		free(img);
		call_right_protocol(specs, lvl);
	}
	alloc_data(specs, lvl, img);
	return (img);
}

/*
** this function needs to be done after the parsing
*/

// void		init_texture(t_rt *specs)
// {
// 	specs->textures[0] = create_texture_image(specs, "textures/posx.xpm", 1);
// 	specs->textures[1] = create_texture_image(specs, "textures/negx.xpm", 1);
// 	specs->textures[2] = create_texture_image(specs, "textures/posy.xpm", 1);
// 	specs->textures[3] = create_texture_image(specs, "textures/negy.xpm", 1);
// 	specs->textures[4] = create_texture_image(specs, "textures/posz.xpm", 1);
// 	specs->textures[5] = create_texture_image(specs, "textures/negz.xpm", 1);
// }

void			draw_image(t_rt *specs)
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
		possible_events_subimage(specs);
	sub2_image(specs);
	mlx_do_sync(specs->mlx);
	if (specs->event == 0)
	{
		destroy_img(specs, specs->img_s);
		sub_image(specs);
		mlx_do_sync(specs->mlx);
		destroy_img(specs, specs->img_s);
		native_image(specs);
		possible_events_native(specs);
	}
}

void			destroy_img(t_rt *specs, t_image *img)
{
	mlx_destroy_image(specs->mlx, img->ptr);
	free(img);
}
