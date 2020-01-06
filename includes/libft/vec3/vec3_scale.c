/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:09:21 by rkamegne          #+#    #+#             */
/*   Updated: 2019/10/04 19:25:06 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_vec3		vec3_scale(t_vec3 v1, double c, char a)
{
	t_vec3	output;
	double	scalar;

	scalar = c;
	if (a == '/' && c != 0)
		scalar = 1 / scalar;
	output.x = v1.x * scalar;
	output.y = v1.y * scalar;
	output.z = v1.z * scalar;
	return (output);
}
