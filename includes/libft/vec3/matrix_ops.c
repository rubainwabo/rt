/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:08:18 by rkamegne          #+#    #+#             */
/*   Updated: 2019/10/04 19:08:21 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_mat3		mat3_unit(void)
{
	t_mat3	unit;

	unit.m[0][0] = 1;
	unit.m[0][1] = 0;
	unit.m[0][2] = 0;
	unit.m[1][0] = 0;
	unit.m[1][1] = 1;
	unit.m[1][2] = 0;
	unit.m[2][0] = 0;
	unit.m[2][1] = 0;
	unit.m[2][2] = 1;
	return (unit);
}

t_vec3		vector_matrix_multiply(t_vec3 one, t_mat3 matrix)
{
	t_vec3	output;

	output.x = matrix.m[0][0] * one.x + matrix.m[0][1] * one.y +
	matrix.m[0][2] * one.z;
	output.y = matrix.m[1][0] * one.x + matrix.m[1][1] * one.y +
	matrix.m[1][2] * one.z;
	output.z = matrix.m[2][0] * one.x + matrix.m[2][1] * one.y +
	matrix.m[2][2] * one.z;
	return (output);
}

void		norme_loop(t_inv *a, t_mat3 *i)
{
	while (++a->k < 3)
	{
		a->tmp = i->m[a->k][a->i];
		a->j = -1;
		while (++a->j < 3)
		{
			if (a->k == a->i)
				break ;
			i->m[a->k][a->j] -= i->m[a->i][a->j] * a->tmp;
			a->unit.m[a->k][a->j] -= a->unit.m[a->i][a->j] * a->tmp;
		}
	}
}

t_mat3		mat3_inv(t_mat3 i)
{
	t_inv	a;

	a.unit = mat3_unit();
	a.i = -1;
	while (++a.i < 3)
	{
		a.tmp = i.m[a.i][a.i];
		a.j = -1;
		while (++a.j < 3)
		{
			i.m[a.i][a.j] /= a.tmp;
			a.unit.m[a.i][a.j] /= a.tmp;
		}
		a.k = -1;
		norme_loop(&a, &i);
	}
	return (a.unit);
}
