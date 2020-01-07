/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:01:25 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/07 20:41:14 by rkamegne         ###   ########.fr       */
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
	mlx_string_put(specs->mlx, specs->win, 20, 500, WHITE, "TEXTURE ON/OFF : ");
	mlx_string_put(specs->mlx, specs->win, 250, 500, GREEN, "T");
}

void	possible_events_subimage(t_rt *specs)
{
	mlx_string_put(specs->mlx, specs->win, 20, 50, WHITE, "CAMERA MOVEMENTS :");
	mlx_string_put(specs->mlx, specs->win, 250, 50, GREEN, "ON");
	mlx_string_put(specs->mlx, specs->win, 20, 100, WHITE, "NATIVE MODE :");
	mlx_string_put(specs->mlx, specs->win, 240, 100, GREEN, "SPACE");
	mlx_string_put(specs->mlx, specs->win, 20, 150, WHITE, "ANTI ALIASING :");
	mlx_string_put(specs->mlx, specs->win, 250, 150, GREEN, "L");
	mlx_string_put(specs->mlx, specs->win, 20, 200, WHITE, "MOVE CAMERA\
															POSITION : ");
	mlx_string_put(specs->mlx, specs->win, 100, 250, GREEN, "ARROW KEYS");
	mlx_string_put(specs->mlx, specs->win, 20, 300, WHITE, "MOVE CAMERA\
															DIRECTION : ");
	mlx_string_put(specs->mlx, specs->win, 100, 350, GREEN, "LEFT MOUSE CLICK");
	mlx_string_put(specs->mlx, specs->win, 20, 400, WHITE, "SAVE IMAGE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 400, GREEN, "S");
	mlx_string_put(specs->mlx, specs->win, 20, 450, WHITE, "TEXTURE ON/OFF : ");
	mlx_string_put(specs->mlx, specs->win, 250, 450, GREEN, "T");
}

void	possible_events_aliasing(t_rt *specs)
{
	mlx_put_image_to_window(specs->mlx, specs->win, specs->ui->ptr, 0, 0);
	mlx_string_put(specs->mlx, specs->win, 20, 50, WHITE, "CAMERA MOVEMENTS :");
	mlx_string_put(specs->mlx, specs->win, 250, 50, RED, "OFF");
	mlx_string_put(specs->mlx, specs->win, 20, 100, WHITE, "ALLOW CAMERA\
																	MOV. :");
	mlx_string_put(specs->mlx, specs->win, 240, 100, GREEN, "SPACE");
	mlx_string_put(specs->mlx, specs->win, 20, 150, WHITE, "ANTI ALIASING :");
	mlx_string_put(specs->mlx, specs->win, 250, 150, RED, "ON");
	mlx_string_put(specs->mlx, specs->win, 20, 200, WHITE, "FILTER SEPIA : ");
	mlx_string_put(specs->mlx, specs->win, 250, 200, GREEN, "D");
	mlx_string_put(specs->mlx, specs->win, 20, 250, WHITE, "FILTER GRAY : ");
	mlx_string_put(specs->mlx, specs->win, 250, 250, GREEN, "A");
	mlx_string_put(specs->mlx, specs->win, 20, 300, WHITE, "STEREO. BLUE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 300, GREEN, "O");
	mlx_string_put(specs->mlx, specs->win, 20, 350, WHITE, "REV. CHANNEL : ");
	mlx_string_put(specs->mlx, specs->win, 250, 350, GREEN, "G");
	mlx_string_put(specs->mlx, specs->win, 20, 400, WHITE, "STEREO. RED : ");
	mlx_string_put(specs->mlx, specs->win, 250, 400, GREEN, "P");
	mlx_string_put(specs->mlx, specs->win, 20, 450, WHITE, "SAVE IMAGE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 450, GREEN, "S");
	mlx_string_put(specs->mlx, specs->win, 20, 500, WHITE, "TEXTURE ON/OFF : ");
	mlx_string_put(specs->mlx, specs->win, 250, 500, GREEN, "T");
}
