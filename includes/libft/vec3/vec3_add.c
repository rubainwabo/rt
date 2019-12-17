/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:08:40 by rkamegne          #+#    #+#             */
/*   Updated: 2019/10/04 20:23:46 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_vec3		vec3_add(t_vec3 v1, t_vec3 v2, char c)
{
	int		oper;
	t_vec3	output;

	oper = 1;
	if (c == '-')
		oper = -1;
	output.x = v1.x + (oper * v2.x);
	output.y = v1.y + (oper * v2.y);
	output.z = v1.z + (oper * v2.z);
	return (output);
}
