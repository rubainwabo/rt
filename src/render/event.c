/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:05:20 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/17 18:07:53 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_image		*create_image(t_rt *specs, char *path)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
    {
        ft_putendl_fd("failed to create the image pointer", 2);
		exit(1);
    }
	img->ptr = mlx_xpm_file_to_image(specs->mlx, path, &img->width, &img->height);
	if (!img->ptr)
    {
        ft_putendl_fd("failed to create the image string", 2);
		exit(1);
    }
	if (!(img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->sizeline, &img->endian)))
        exit(1);
	return (img);
}

void		init_texture(t_rt *specs)
{
	specs->textures[0] = create_image(specs, "textures/posx.xpm");
	specs->textures[1] = create_image(specs, "textures/negx.xpm");
	specs->textures[2] = create_image(specs, "textures/posy.xpm");
	specs->textures[3] = create_image(specs, "textures/negy.xpm");
	specs->textures[4] = create_image(specs, "textures/posz.xpm");
	specs->textures[5] = create_image(specs, "textures/negz.xpm");
}

/*
** simple trick converting char to unsigned char to fix overflows
*/

void		apply_sepia(t_rt *specs)
{
	t_var	v;
	int		i;

	i = 0;
	int comp = H_IMG * W_IMG * 4;
	while (i < comp)
	{
		v.red = ft_min(255.0, (((unsigned char)specs->img_str[i + 2] * .393) + ((unsigned char)specs->img_str[i + 1] * .769) + ((unsigned char)specs->img_str[i] * .189)));
		v.green = ft_min(255.0, (((unsigned char)specs->img_str[i + 2] * .349) + ((unsigned char)specs->img_str[i + 1] * .686) + ((unsigned char)specs->img_str[i] * .168)));
		v.blue = ft_min(255.0, (((unsigned char)specs->img_str[i + 2] * .272) + ((unsigned char)specs->img_str[i + 1] * .534) + ((unsigned char)specs->img_str[i] * .131)));
		specs->img_str[i + 2] = v.red;
		specs->img_str[i + 1] = v.green;
		specs->img_str[i] = v.blue;
		i += 4;
	}
}

/*
** filter_str contents the default string without filters
*/

int			draw_image(t_rt *specs)
{
	if (!(specs->img = mlx_new_image(specs->mlx, W_IMG, H_IMG)))
		return (0);
	if (!(specs->img_str = mlx_get_data_addr(specs->img, &specs->bpp,
	&specs->size_line, &specs->endian)))
		return (0);
	//init_texture(specs);
	launch_threads(specs, THREAD_COUNT);
	if (specs->event == 1)
		apply_sepia(specs);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img, 0, 0);
	return (1);
}

int			deal_key(int key, t_rt *specs)
{
	if (key == 0)
	{
		specs->event = !specs->event;
		draw_image(specs);
	}
	if (key == LEFT)
	{
		specs->camera.x -= 0.25;
		draw_image(specs);
	}
	if (key == UP)
	{
		specs->camera.y += 0.25;
		draw_image(specs);
	}
	if (key == DOWN)
	{
		specs->camera.y -= 0.25;
		draw_image(specs);
	}
	if (key == 53)
		exit_protocol2(specs, 19, "exit with code 0");
	return (0);
}
