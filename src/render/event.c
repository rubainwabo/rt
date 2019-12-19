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

	if (specs->event == 1)  // this caps the maximum call of apply_sepia by the corresponding event
		return ;
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
	specs->event = 1;
}

void		apply_grayscale(t_rt *specs)
{
	int comp = H_IMG * W_IMG * 4;
	int	i;
	int	gray;

	if (specs->event == 2)  // this caps the maximum call of apply_grayscale by the corresponding event
		return ;
	i = 0;
	while (i < comp)
	{
		gray = (int)(((unsigned char)specs->img_str2[i + 2] * 0.3) + ((unsigned char)specs->img_str2[i + 1] * 0.59) + ((unsigned char)specs->img_str2[i] * 0.11));
		specs->img_str2[i + 2] = gray;
		specs->img_str2[i + 1] = gray;
		specs->img_str2[i] = gray;
		i += 4;
	}
	specs->event = 2;
}

void		apply_blue(t_rt *specs)
{
	int comp = H_IMG * W_IMG * 4;
	int	i;
	int	gray;

	if (specs->event == 3)  // this caps the maximum call of apply_grayscale by the corresponding event
		return ;
	i = 0;
	while (i < comp)
	{
		gray = (int)(((unsigned char)specs->img_str2[i + 2] * 0.3) + ((unsigned char)specs->img_str2[i + 1] * 0.59) + ((unsigned char)specs->img_str2[i] * 0.11));
		specs->img_str2[i + 2] = 0;
		specs->img_str2[i + 1] = gray;
		specs->img_str2[i] = gray;
		i += 4;
	}
	specs->event = 3;
}

void		apply_purple(t_rt *specs)
{
	int comp = H_IMG * W_IMG * 4;
	int	i;
	int	gray;

	if (specs->event == 4)  // this caps the maximum call of apply_grayscale by the corresponding event
		return ;
	i = 0;
	while (i < comp)
	{
		gray = (int)(((unsigned char)specs->img_str2[i + 2] * 0.3) + ((unsigned char)specs->img_str2[i + 1] * 0.59) + ((unsigned char)specs->img_str2[i] * 0.11));
		specs->img_str2[i + 2] = gray;
		specs->img_str2[i + 1] = gray;
		specs->img_str2[i] = 0;
		i += 4;
	}
	specs->event = 4;
}

void		apply_green(t_rt *specs)
{
	int comp = H_IMG * W_IMG * 4;
	int	i;
	int	gray;

	if (specs->event == 5)  // this caps the maximum call of apply_grayscale by the corresponding event
		return ;
	i = 0;
	while (i < comp)
	{
		gray = (int)(((unsigned char)specs->img_str2[i + 2] * 0.3) + ((unsigned char)specs->img_str2[i + 1] * 0.59) + ((unsigned char)specs->img_str2[i] * 0.11));
		specs->img_str2[i + 2] = 0;
		specs->img_str2[i + 1] = gray;
		specs->img_str2[i] = 0;
		i += 4;
	}
	specs->event = 5;
}

/*
** filter_str contents the default string without filters
*/

void		super_sampling(t_rt *specs)
{
	int		i;
	int		j;
	t_var	v;

	i = 0;
	while (i < H_IMG) // H_IMG and W_IMG are the size of the native image
	{
		j = 0;
		while (j < W_IMG)
		{
			v.coord[0] = (j * 8) + (i * 2) * specs->size_line;
			v.coord[1] = (j * 8) + 4 + (i * 2) * specs->size_line;
			v.coord[2] = (j * 8) + ((i * 2) + 1) * specs->size_line;
			v.coord[3] = (j * 8) + 4  + ((i * 2) + 1) * specs->size_line;
			ft_memcpy(&v.pix[0], specs->img_str + v.coord[0], 4);
			ft_memcpy(&v.pix[1], specs->img_str + v.coord[1], 4);
			ft_memcpy(&v.pix[2], specs->img_str + v.coord[2], 4);
			ft_memcpy(&v.pix[3], specs->img_str + v.coord[3], 4);
			v.coord[4] = i * specs->size_line2 + (j * 4);
			specs->img_str2[v.coord[4]] = (((v.pix[0] & 0xff) + (v.pix[1] & 0xff) + (v.pix[2] & 0xff) + (v.pix[3] & 0xff)) / 4);
			specs->img_str2[v.coord[4] + 1] = ((((v.pix[0] >> 8) & 0xff) + ((v.pix[1] >> 8) & 0xff) + ((v.pix[2] >> 8) & 0xff) + ((v.pix[3] >> 8) & 0xff)) / 4);
			specs->img_str2[v.coord[4] + 2] = ((((v.pix[0] >> 16) & 0xff) + ((v.pix[1] >> 16) & 0xff) + ((v.pix[2] >> 16) & 0xff) + ((v.pix[3] >> 16) & 0xff)) / 4);
			j++;
		}
		i++;
	}
}

void		sub_sampling(t_rt *specs)
{
	int		i;
	int		j;
	t_var	v;

	i = 0;
	while (i < specs->h_img)
	{
		j = 0;
		while (j < specs->w_img)
		{
			v.coord[4] = (j * 4) + i * specs->size_line;
			ft_memcpy(&v.pix[0], specs->img_str + v.coord[4], 4);
			v.coord[0] = (j * 8) + i * 2 * specs->size_line2 ;
			v.coord[1] = v.coord[0] + 4;
			v.coord[2] = (j * 8) + ((i * 2) + 1) * specs->size_line2;
			v.coord[3] = v.coord[2] + 4;
			// pixel1
			specs->img_str2[v.coord[0]] = v.pix[0] & 0xff;
			specs->img_str2[v.coord[0] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_str2[v.coord[0] + 2] = (v.pix[0] >> 16) & 0xff;
			// pixel2
			specs->img_str2[v.coord[1]] = v.pix[0] & 0xff;
			specs->img_str2[v.coord[1] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_str2[v.coord[1] + 2] = (v.pix[0] >> 16) & 0xff;
			// pixel3
			specs->img_str2[v.coord[2]] = v.pix[0] & 0xff;
			specs->img_str2[v.coord[2] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_str2[v.coord[2] + 2] = (v.pix[0] >> 16) & 0xff;
			// pixel4
			specs->img_str2[v.coord[3]] = v.pix[0] & 0xff;
			specs->img_str2[v.coord[3] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_str2[v.coord[3] + 2] = (v.pix[0] >> 16) & 0xff;
			j++;
		}
		i++;
	}
}

/*
** img2 and img_str2 are the identifiers of the image that is always going to be printed
** img and img_str are either the sub or super sampling
*/

// void		put_to_window(t_rt *specs)
// {
	
// }

int		super_image(t_rt *specs)
{
	specs->w_img = W_IMG * 2;
	specs->h_img = H_IMG * 2;
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
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img2, 0, 0);
	return (1);
}

int		sub_image(t_rt *specs)
{
	specs->w_img = W_IMG / 2;
	specs->h_img = H_IMG / 2;
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
	sub_sampling(specs);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img2, 0, 0);
	return (1);
}

int			draw_image(t_rt *specs)
{
	if (specs->event == 3)  // this caps the maximum call of draw_image by the corresponding event
		return (1);
	sub_image(specs);
	specs->w_img = W_IMG;
	specs->h_img = H_IMG;
	mlx_do_sync(specs->mlx);
	if (!(specs->img = mlx_new_image(specs->mlx, W_IMG, H_IMG)))
		return (0);
	if (!(specs->img_str = mlx_get_data_addr(specs->img, &specs->bpp,
	&specs->size_line, &specs->endian)))
		return (0);
	// if (!(specs->img2 = mlx_new_image(specs->mlx, W_IMG, H_IMG)))
	// 	return (0);
	// if (!(specs->img_str2 = mlx_get_data_addr(specs->img, &specs->bpp,
	// &specs->size_line2, &specs->endian)))
	//	return (0);
	launch_threads(specs, THREAD_COUNT);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img, 0, 0);
	mlx_do_sync(specs->mlx);
	super_image(specs);
	specs->event = 3;
	return (1);
}

int			deal_key(int key, t_rt *specs)
{
	if (key == S)
	{
		apply_grayscale(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img2, 0, 0);
	}
	if (key == A)
	{
		apply_sepia(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img2, 0, 0);
	}
	if (key == F)
	{
		apply_blue(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img2, 0, 0);
	}
	if (key == G)
	{
		apply_green(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img2, 0, 0);
	}
	if (key == H)
	{
		apply_purple(specs);
		mlx_put_image_to_window(specs->mlx, specs->win, specs->img2, 0, 0);
	}
	if (key == D)
		draw_image(specs);
	if (key == RIGHT)
	{
		specs->camera.x -= 0.25;
		draw_image(specs);
	}
	if (key == LEFT)
	{
		specs->camera.x += 0.25;
		draw_image(specs);
	}
	if (key == UP)
	{
		specs->camera.y -= 0.25;
		draw_image(specs);
	}
	if (key == DOWN)
	{
		specs->camera.y += 0.25;
		draw_image(specs);
	}
	if (key == 53)
		exit_protocol2(specs, 19, "exit with code 0");
	return (0);
}
