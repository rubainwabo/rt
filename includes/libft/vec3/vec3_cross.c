/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 19:08:52 by rkamegne          #+#    #+#             */
/*   Updated: 2019/10/04 19:08:53 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	output;

	output.x = v1.y * v2.z - v2.y * v1.z;
	output.y = v2.x * v1.z - v1.x * v2.z;
	output.z = v1.x * v2.y - v2.x * v1.y;
	return (output);
}
