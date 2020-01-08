/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:44:36 by rkamegne          #+#    #+#             */
/*   Updated: 2020/01/08 16:34:26 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	possible_events_textures(t_rt *specs)
{
	mlx_string_put(specs->mlx, specs->win, 20, 650, WHITE,
										"PLANE TEXTURES STRETCH :");
	mlx_string_put(specs->mlx, specs->win, 210, 700, GREEN, "X C");
	mlx_string_put(specs->mlx, specs->win, 20, 550, WHITE,
										"SPHERE TEXTURES MOVEMENTS :");
	mlx_string_put(specs->mlx, specs->win, 210, 600, GREEN, "V B N M");
	mlx_string_put(specs->mlx, specs->win, 20, 450, WHITE,
													"TEXTURE ON/OFF : ");
	mlx_string_put(specs->mlx, specs->win, 250, 450, GREEN, "U");
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
	mlx_string_put(specs->mlx, specs->win, 100, 250, GREEN, "ARROW KEYS 2 8");
	mlx_string_put(specs->mlx, specs->win, 20, 300, WHITE, "MOVE CAMERA\
															DIRECTION : ");
	mlx_string_put(specs->mlx, specs->win, 100, 350, GREEN, "LEFT MOUSE CLICK");
	mlx_string_put(specs->mlx, specs->win, 20, 400, WHITE, "SAVE IMAGE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 400, GREEN, "S");
	mlx_string_put(specs->mlx, specs->win, 20, 450, WHITE, "TEXTURE ON/OFF : ");
	mlx_string_put(specs->mlx, specs->win, 250, 450, GREEN, "U");
	mlx_string_put(specs->mlx, specs->win, 20, 500, WHITE,
													"SWAP SYBOX TEXTURE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 500, GREEN, "T");
	possible_events_textures(specs);
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
	mlx_string_put(specs->mlx, specs->win, 20, 550, WHITE,
													"SWAP SYBOX TEXTURE : ");
	mlx_string_put(specs->mlx, specs->win, 250, 550, GREEN, "T");
	mlx_string_put(specs->mlx, specs->win, 20, 500, WHITE, "TEXTURE ON/OFF : ");
	mlx_string_put(specs->mlx, specs->win, 250, 500, GREEN, "U");
}
