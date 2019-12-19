/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:05:20 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/19 15:26:26 by rkamegne         ###   ########.fr       */
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
		v.red = ft_min(255.0, (((unsigned char)specs->img_str2[i + 2] * .393) + ((unsigned char)specs->img_str2[i + 1] * .769) + ((unsigned char)specs->img_str2[i] * .189)));
		v.green = ft_min(255.0, (((unsigned char)specs->img_str2[i + 2] * .349) + ((unsigned char)specs->img_str2[i + 1] * .686) + ((unsigned char)specs->img_str2[i] * .168)));
		v.blue = ft_min(255.0, (((unsigned char)specs->img_str2[i + 2] * .272) + ((unsigned char)specs->img_str2[i + 1] * .534) + ((unsigned char)specs->img_str2[i] * .131)));
		specs->img_str2[i + 2] = v.red;
		specs->img_str2[i + 1] = v.green;
		specs->img_str2[i] = v.blue;
		i += 4;
	}
}

void		apply_grayscale(t_rt *specs)
{
	int comp = H_IMG * W_IMG * 4;
	int	i;
	int	gray;

	i = 0;
	while (i < comp)
	{
		gray = (int)(((unsigned char)specs->img_str2[i + 2] * 0.3) + ((unsigned char)specs->img_str2[i + 1] * 0.59) + ((unsigned char)specs->img_str2[i] * 0.11));
		specs->img_str2[i + 2] = gray;
		specs->img_str2[i + 1] = gray;
		specs->img_str2[i] = gray;
		i += 4;
	}
}

/*
** filter_str contents the default string without filters
*/

void		super_sampling(t_rt *specs)
{
	int		pixel1, pixel2, pixel3, pixel4, i, j, coord, coord1, coord2, coord3, coord4;
	int		comp, comp2, x1, x2, x3, x4, y1, y2, y3, y4;

	i = 0;
	pixel1 = 0;
	pixel2 = 0;
	pixel3 = 0;
	pixel4 = 0;
	coord = 0;
	coord2 = 0;
	while (i < H_IMG)
	{
		j = 0;
		y1 = i * 2;
		y2 = y1;
		y3 = y1 + 1;
		y4 = y3;
		while (j < W_IMG)
		{
			x1 = j * 8;
			x2 = x1 + 4;
			x3 = x1;
			x4 = x2;
			coord1 = x1 + y1 * specs->size_line;
			coord2 = x2 + y2 * specs->size_line;
			coord3 = x3 + y3 * specs->size_line;
			coord4 = x4 + y4 * specs->size_line;
			ft_memcpy(&pixel1, specs->img_str + coord1, 4);
			ft_memcpy(&pixel2, specs->img_str + coord2, 4);
			ft_memcpy(&pixel3, specs->img_str + coord3, 4);
			ft_memcpy(&pixel4, specs->img_str + coord4, 4);
			coord = i * specs->size_line2 + (j * 4);
			specs->img_str2[coord] = (((pixel1 & 0xff) + (pixel2 & 0xff) + (pixel3 & 0xff) + (pixel4 & 0xff)) / 4);
			specs->img_str2[coord + 1] = ((((pixel1 >> 8) & 0xff) + ((pixel2 >> 8) & 0xff) + ((pixel3 >> 8) & 0xff) + ((pixel4 >> 8) & 0xff)) / 4);
			specs->img_str2[coord + 2] = ((((pixel1 >> 16) & 0xff) + ((pixel2 >> 16) & 0xff) + ((pixel3 >> 16) & 0xff) + ((pixel4 >> 16) & 0xff)) / 4);
			j++;
		}
		i++;
	}
}

int			draw_image(t_rt *specs)
{
	if (!(specs->img = mlx_new_image(specs->mlx, specs->w_img, specs->h_img)))
		return (0);
	if (!(specs->img_str = mlx_get_data_addr(specs->img, &specs->bpp,
	&specs->size_line, &specs->endian)))
		return (0);
	if (!(specs->img2 = mlx_new_image(specs->mlx, W_IMG, H_IMG)))
		return (0);
	if (!(specs->img_str2 = mlx_get_data_addr(specs->img2, &specs->bpp,
	&specs->size_line2, &specs->endian)))
		return (0);
	launch_threads(specs, THREAD_COUNT);
	super_sampling(specs);
	if (specs->event == 1)
		apply_sepia(specs);
	else if (specs->event == 2)
		apply_grayscale(specs);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img2, 0, 0);
	return (1);
}

int			deal_key(int key, t_rt *specs)
{
	if (key == 1)
	{
		specs->event = 2;
		draw_image(specs);
	}
	if (key == 0)
	{
		specs->event = 1;
		draw_image(specs);
	}
	if (key == 2)
	{
		specs->event = 0;
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
