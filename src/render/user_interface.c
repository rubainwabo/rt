#include "rtv1.h"

void	init_ui_img(t_image *img, t_rt *specs)
{
	img->ptr = mlx_new_image(specs->mlx, POS_X, HEIGHT);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->sizeline, &img->endian);
}

void    draw_backgrd(t_rt *specs)
{
	int		i;
	t_image	img;

	init_ui_img(&img, specs);
	i = 0;
	while (i < HEIGHT * POS_X * 4)
	{
		img.data[i] = 0x000011 & 0xff;
		img.data[i + 1] = 0;
		img.data[i + 2] = 0;
		i += 4;
	}
	mlx_put_image_to_window(specs->mlx, specs->win, img.ptr, 0, 0);
}

void	possible_events2(t_rt *specs)
{
	draw_backgrd(specs);
	mlx_string_put(specs->mlx, specs->win, 20, 50, WHITE, "CAMERA MOVEMENTS :");
	mlx_string_put(specs->mlx, specs->win, 200, 50, RED, "OFF");
	mlx_string_put(specs->mlx, specs->win, 20, 100, WHITE, "ALLOW CAMERA MOVEMENT :");
	mlx_string_put(specs->mlx, specs->win, 200, 100, GREEN, "SPACE");
	mlx_string_put(specs->mlx, specs->win, 20, 150, WHITE, "ANTI ALIASING :");
	mlx_string_put(specs->mlx, specs->win, 200, 150, GREEN, "L");
	mlx_string_put(specs->mlx, specs->win, 20, 200, WHITE, "FILTER SEPIA : ");
	mlx_string_put(specs->mlx, specs->win, 200, 200, GREEN, "S");
	mlx_string_put(specs->mlx, specs->win, 20, 250, WHITE, "FILTER GRAY : ");
	mlx_string_put(specs->mlx, specs->win, 200, 250, GREEN, "A");
	mlx_string_put(specs->mlx, specs->win, 20, 300, WHITE, "FILTER BLUE : ");
	mlx_string_put(specs->mlx, specs->win, 200, 300, GREEN, "F");
	mlx_string_put(specs->mlx, specs->win, 20, 350, WHITE, "FILTER GREEN : ");
	mlx_string_put(specs->mlx, specs->win, 200, 350, GREEN, "G");
	mlx_string_put(specs->mlx, specs->win, 20, 400, WHITE, "FILTER PURPLE : ");
	mlx_string_put(specs->mlx, specs->win, 200, 400, GREEN, "H");
}

void	possible_events(t_rt *specs)
{
	mlx_string_put(specs->mlx, specs->win, 20, 50, WHITE, "CAMERA MOVEMENTS :");
	mlx_string_put(specs->mlx, specs->win, 200, 50, GREEN, "ON");
	mlx_string_put(specs->mlx, specs->win, 20, 100, WHITE, "NATIVE MODE :");
	mlx_string_put(specs->mlx, specs->win, 200, 100, GREEN, "SPACE");
	mlx_string_put(specs->mlx, specs->win, 20, 150, WHITE, "ANTI ALIASING :");
	mlx_string_put(specs->mlx, specs->win, 200, 150, GREEN, "L");
	mlx_string_put(specs->mlx, specs->win, 20, 200, WHITE, "MOVE CAMERA POSITION : ");
	mlx_string_put(specs->mlx, specs->win, 200, 200, GREEN, "ARROW KEYS");
	mlx_string_put(specs->mlx, specs->win, 20, 250, WHITE, "MOVE CAMERA DIRECTION : ");
	mlx_string_put(specs->mlx, specs->win, 200, 250, GREEN, "LEFT MOUSE CLICK");
}