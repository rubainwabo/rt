
#include "rt.h"

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
			v.coord[0] = (j * 8) + (i * 2) * specs->img->sizeline;
			v.coord[1] = (j * 8) + 4 + (i * 2) * specs->img->sizeline;
			v.coord[2] = (j * 8) + ((i * 2) + 1) * specs->img->sizeline;
			v.coord[3] = (j * 8) + 4  + ((i * 2) + 1) * specs->img->sizeline;
			ft_memcpy(&v.pix[0], specs->img->data + v.coord[0], 4);
			ft_memcpy(&v.pix[1], specs->img->data + v.coord[1], 4);
			ft_memcpy(&v.pix[2], specs->img->data + v.coord[2], 4);
			ft_memcpy(&v.pix[3], specs->img->data + v.coord[3], 4);
			v.coord[4] = i * specs->img_s->sizeline + (j * 4);
			specs->img_s->data[v.coord[4]] = (((v.pix[0] & 0xff) + (v.pix[1] & 0xff) + (v.pix[2] & 0xff) + (v.pix[3] & 0xff)) / 4);
			specs->img_s->data[v.coord[4] + 1] = ((((v.pix[0] >> 8) & 0xff) + ((v.pix[1] >> 8) & 0xff) + ((v.pix[2] >> 8) & 0xff) + ((v.pix[3] >> 8) & 0xff)) / 4);
			specs->img_s->data[v.coord[4] + 2] = ((((v.pix[0] >> 16) & 0xff) + ((v.pix[1] >> 16) & 0xff) + ((v.pix[2] >> 16) & 0xff) + ((v.pix[3] >> 16) & 0xff)) / 4);
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
			v.coord[4] = (j * 4) + i * specs->img->sizeline;
			ft_memcpy(&v.pix[0], specs->img->data + v.coord[4], 4);
			v.coord[0] = (j * 8) + i * 2 * specs->img_s->sizeline ;
			v.coord[1] = v.coord[0] + 4;
			v.coord[2] = (j * 8) + ((i * 2) + 1) * specs->img_s->sizeline;
			v.coord[3] = v.coord[2] + 4;
			// pixel1
			specs->img_s->data[v.coord[0]] = v.pix[0] & 0xff;
			specs->img_s->data[v.coord[0] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_s->data[v.coord[0] + 2] = (v.pix[0] >> 16) & 0xff;
			// pixel2
			specs->img_s->data[v.coord[1]] = v.pix[0] & 0xff;
			specs->img_s->data[v.coord[1] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_s->data[v.coord[1] + 2] = (v.pix[0] >> 16) & 0xff;
			// pixel3
			specs->img_s->data[v.coord[2]] = v.pix[0] & 0xff;
			specs->img_s->data[v.coord[2] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_s->data[v.coord[2] + 2] = (v.pix[0] >> 16) & 0xff;
			// pixel4
			specs->img_s->data[v.coord[3]] = v.pix[0] & 0xff;
			specs->img_s->data[v.coord[3] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_s->data[v.coord[3] + 2] = (v.pix[0] >> 16) & 0xff;
			j++;
		}
		i++;
	}
}


void		fill(t_rt *specs, int coord, int pix)
{
	specs->img_s->data[coord] = pix & 0xff;
	specs->img_s->data[coord + 1] = (pix >> 8) & 0xff;
	specs->img_s->data[coord + 2] = (pix >> 16) & 0xff;
}

void		sub2_sampling(t_rt *specs)
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
			v.coord[16] = (j * 4) + i * specs->img->sizeline;
			ft_memcpy(&v.pix[0], specs->img->data + v.coord[16], 4);
			v.coord[0] = (j * 16) + i * 4 * specs->img_s->sizeline ;
			v.coord[1] = v.coord[0] + 4;
			v.coord[2] = v.coord[0] + 8;
			v.coord[3] = v.coord[0] + 12;
			v.coord[4] = (j * 16) + ((i * 4) + 1) * specs->img_s->sizeline;
			v.coord[5] = v.coord[4] + 4;
			v.coord[6] = v.coord[4] + 8;
			v.coord[7] = v.coord[4] + 12;
			v.coord[8] = (j * 16) + ((i * 4) + 2) * specs->img_s->sizeline;
			v.coord[9] = v.coord[8] + 4;
			v.coord[10] = v.coord[8] + 8;
			v.coord[11] = v.coord[8] + 12;
			v.coord[12] = (j * 16) + ((i * 4) + 3) * specs->img_s->sizeline;
			v.coord[13] = v.coord[12] + 4;
			v.coord[14] = v.coord[12] + 8;
			v.coord[15] = v.coord[12] + 12;
			// pixel1
			specs->img_s->data[v.coord[0]] = v.pix[0] & 0xff;
			specs->img_s->data[v.coord[0] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_s->data[v.coord[0] + 2] = (v.pix[0] >> 16) & 0xff;
			// pixel2
			specs->img_s->data[v.coord[1]] = v.pix[0] & 0xff;
			specs->img_s->data[v.coord[1] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_s->data[v.coord[1] + 2] = (v.pix[0] >> 16) & 0xff;
			// pixel3
			specs->img_s->data[v.coord[2]] = v.pix[0] & 0xff;
			specs->img_s->data[v.coord[2] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_s->data[v.coord[2] + 2] = (v.pix[0] >> 16) & 0xff;
			// pixel4
			specs->img_s->data[v.coord[3]] = v.pix[0] & 0xff;
			specs->img_s->data[v.coord[3] + 1] = (v.pix[0] >> 8) & 0xff;
			specs->img_s->data[v.coord[3] + 2] = (v.pix[0] >> 16) & 0xff;
			fill(specs, v.coord[4], v.pix[0]);
			fill(specs, v.coord[5], v.pix[0]);
			fill(specs, v.coord[6], v.pix[0]);
			fill(specs, v.coord[7], v.pix[0]);
			fill(specs, v.coord[8], v.pix[0]);
			fill(specs, v.coord[9], v.pix[0]);
			fill(specs, v.coord[10], v.pix[0]);
			fill(specs, v.coord[11], v.pix[0]);
			fill(specs, v.coord[12], v.pix[0]);
			fill(specs, v.coord[13], v.pix[0]);
			fill(specs, v.coord[14], v.pix[0]);
			fill(specs, v.coord[15], v.pix[0]);
			j++;
		}
		i++;
	}
}

/*
** img2 and img_s->data are the identifiers of the image that is always going to be printed
** img and img_str are either the sub or super sampling
*/

void    super_image(t_rt *specs)
{
	specs->w_img = W_IMG * 2;
	specs->h_img = H_IMG * 2;
    specs->img = create_image(specs, NULL, specs->w_img, specs->h_img);
    specs->img_s = create_image(specs, NULL, W_IMG, H_IMG);
	launch_threads(specs, THREAD_COUNT);
	super_sampling(specs);
    destroy_img(specs, specs->img);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
}

void    sub_image(t_rt *specs)
{
	specs->w_img = W_IMG / 2;
	specs->h_img = H_IMG / 2;
    specs->img = create_image(specs, NULL, specs->w_img, specs->h_img);
    specs->img_s = create_image(specs, NULL, W_IMG, H_IMG);
	launch_threads(specs, THREAD_COUNT);
	sub_sampling(specs);
    destroy_img(specs, specs->img);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
}

void    sub2_image(t_rt *specs)
{
	specs->w_img = W_IMG / 4;
	specs->h_img = H_IMG / 4;
    specs->img = create_image(specs, NULL, specs->w_img, specs->h_img);
    specs->img_s = create_image(specs, NULL, W_IMG, H_IMG);
	launch_threads(specs, THREAD_COUNT);
	sub2_sampling(specs);
    destroy_img(specs, specs->img);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
}

void    native_image(t_rt *specs)
{
    int     i;
    int     size;

    i = -1;
    size = W_IMG * H_IMG * 4;
	specs->w_img = W_IMG;
	specs->h_img = H_IMG;
    specs->img = create_image(specs, NULL, specs->w_img, specs->h_img);
    specs->img_s = create_image(specs, NULL, W_IMG, H_IMG);
	launch_threads(specs, THREAD_COUNT);
    while (++i < size)
    {
        specs->img_s->data[i] = specs->img->data[i];
    }
    destroy_img(specs, specs->img);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img_s->ptr, POS_X, POS_Y);
}