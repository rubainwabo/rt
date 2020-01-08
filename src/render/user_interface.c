/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:01:25 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/08 15:54:59 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_img_backgrd(t_rt *specs)
{
	int		i;
	int		size;

	size = HEIGHT * POS_X * 4;
	specs->ui = create_image(specs, 0, POS_X, HEIGHT);
	i = 0;
	while (i < size)
	{
		specs->ui->data[i] = ((int)(0x000088 * (double)i / size)) & 0xff;
		specs->ui->data[i + 1] = 0;
		specs->ui->data[i + 2] = 0;
		i += 4;
	}
}

void	possible_events_native(t_rt *specs)
{
	mlx_put_image_to_window(specs->mlx, specs->win, specs->ui->ptr, 0, 0);
	mlx_string_put(specs->mlx, specs->win, 20, 50, WHITE, "CAMERA MOVEMENTS :");
	mlx_string_put(specs->mlx, specs->win, 250, 50, RED, "OFF");
	mlx_string_put(specs->mlx, specs->win, 20, 100, WHITE, "ALLOW CAMERA\
																	MOV. :");
	mlx_string_put(specs->mlx, specs->win, 240, 100, GREEN, "SPACE");
	mlx_string_put(specs->mlx, specs->win, 20, 150, WHITE, "ANTI ALIASING :");
	mlx_string_put(specs->mlx, specs->win, 250, 150, GREEN, "L");
	mlx_string_put(specs->mlx, specs->win, 20, 200, WHITE, "FILTER SEPIA : ");
	mlx_string_put(specs->mlx, specs->win, 250, 200, GREEN, "D");
	mlx_string_put(specs->mlx, specs->win, 20, 250, WHITE, "FILTER GRAY : ");
	mlx_string_put(specs->mlx, specs->win, 250, 250, GREEN, "A");
	mlx_string_put(specs->mlx, specs->win, 20, 300, WHITE, "STEREO. BLUE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 300, GREEN, "O");
	mlx_string_put(specs->mlx, specs->win, 20, 350, WHITE, "REV. CHANNEL : ");
	mlx_string_put(specs->mlx, specs->win, 250, 350, GREEN, "G");
	mlx_string_put(specs->mlx, specs->win, 20, 400, WHITE, "STEREO. BLUE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 400, GREEN, "P");
	mlx_string_put(specs->mlx, specs->win, 20, 450, WHITE, "SAVE IMAGE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 450, GREEN, "S");
	mlx_string_put(specs->mlx, specs->win, 20, 550, WHITE,
													"SWAP SYBOX TEXTURE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 550, GREEN, "T");
	mlx_string_put(specs->mlx, specs->win, 20, 500, WHITE, "TEXTURE ON/OFF : ");
	mlx_string_put(specs->mlx, specs->win, 250, 500, GREEN, "U");
}

void	turn_off_text(t_obj *list, t_sphere *s)
{
	if (list->id == 1)
	{
		s = (t_sphere *)list->obj;
		if (s->surf->text && s->surf->text_status)
			s->surf->text = 0;
		else if (!s->surf->text && s->surf->text_status)
			s->surf->text = 1;
	}
}

void	turn_on_off_textures(t_rt *specs)
{
	t_plane		*p;
	t_sphere	*s;
	t_obj		*list;

	list = specs->obj_list;
	s = NULL;
	while (list)
	{
		if (list->id == 0)
		{
			p = (t_plane *)list->obj;
			if (p->surf->text && p->surf->text_status)
				p->surf->text = 0;
			else if (!p->surf->text && p->surf->text_status)
				p->surf->text = 1;
		}
		turn_off_text(list, s);
		list = list->next;
	}
}
