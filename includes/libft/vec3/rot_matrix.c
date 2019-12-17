/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:55:04 by rkamegne          #+#    #+#             */
/*   Updated: 2019/10/04 18:59:24 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_mat3		rotation_matrix_x(double angle)
{
	t_mat3	output;

	output.m[0][0] = 1;
	output.m[0][1] = 0;
	output.m[0][2] = 0;
	output.m[1][0] = 0;
	output.m[1][1] = cos(M_PI * angle / 180);
	output.m[1][2] = -sin(M_PI * angle / 180);
	output.m[2][0] = 0;
	output.m[2][1] = sin(M_PI * angle / 180);
	output.m[2][2] = cos(M_PI * angle / 180);
	return (output);
}

t_mat3		rotation_matrix_y(double angle)
{
	t_mat3	output;

	output.m[0][0] = cos(M_PI * angle / 180);
	output.m[0][1] = 0;
	output.m[0][2] = sin(M_PI * angle / 180);
	output.m[1][0] = 0;
	output.m[1][1] = 1;
	output.m[1][2] = 0;
	output.m[2][0] = -sin(M_PI * angle / 180);
	output.m[2][1] = 0;
	output.m[2][2] = cos(M_PI * angle / 180);
	return (output);
}

t_mat3		rotation_matrix_z(double angle)
{
	t_mat3	output;

	output.m[0][0] = cos(M_PI * angle / 180);
	output.m[0][1] = -sin(M_PI * angle / 180);
	output.m[0][2] = 0;
	output.m[1][0] = sin(M_PI * angle / 180);
	output.m[1][1] = cos(M_PI * angle / 180);
	output.m[1][2] = 0;
	output.m[2][0] = 0;
	output.m[2][1] = 0;
	output.m[2][2] = 1;
	return (output);
}
