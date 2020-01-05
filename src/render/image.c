#include "rtv1.h"

static void	alloc_data(t_rt *specs, t_image *img)
{
	if (!(img->data = mlx_get_data_addr(img->ptr, &img->bpp,
		&img->sizeline, &img->endian)))
	{
		free(img);
		free(img->ptr);
		exit_protocol(specs, -1, "failed to created the img string");
	}
}

t_image		*create_image(t_rt *specs, char *path, int x, int y)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
		exit_protocol(specs, -1, "img struct malloc failed");
	if (!path)
		img->ptr = mlx_new_image(specs->mlx, x, y);
	else
		img->ptr = mlx_xpm_file_to_image(specs->mlx, path,
		&img->width, &img->height);
	if (!img->ptr)
	{
		free(img);
		exit_protocol(specs, -1, "failed to created the img pointer");
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
	draw_backgrd(specs);
	if (specs->event == NO_EVENT)
		mlx_string_put(specs->mlx, specs->win, 100, 300, WHITE, "LOADING...");
	else
		possible_events(specs);
	sub2_image(specs);
	if (specs->event == NO_EVENT)
	{
   		destroy_img(specs, specs->img_s);
		sub_image(specs);
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