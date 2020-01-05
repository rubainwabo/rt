/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:57:47 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/09 19:13:13 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		advance(char **str, t_rt *specs)
{
	while (**str && **str != ',')
		(*str)++;
	(*str)++;
	if (!**str)
		exit_protocol(specs, 0, "Error in the parser (advance)");
}

char			*move(int *i, int *j, t_rt *specs)
{
	char	*str;

	(*i)++;
	*j = 0;
	if (*i >= specs->nb_line)
		exit_protocol(specs, 0, "Error in the parser (move)");
	while (specs->input[*i][*j] && specs->input[*i][*j] != '(')
		(*j)++;
	str = ft_strtrim(&specs->input[*i][*j]);
	if (!*str || specs->input[*i][*j] != '(')
	{
		free(str);
		exit_protocol(specs, 0, "Error in move");
	}
	free(str);
	return (&specs->input[*i][++(*j)]);
}

void			parse_vec(t_vec3 *ptr, char *input, t_rt *specs)
{
	if (!ft_strchr(input, ','))
		exit_protocol(specs, 0, "Error in parse_vec");
	ptr->x = ft_atof(input);
	advance(&input, specs);
	ptr->y = ft_atof(input);
	advance(&input, specs);
	ptr->z = ft_atof(input);
}

void			parse_vec_norm(t_vec3 *ptr, char *input, t_rt *specs)
{
	if (!ft_strchr(input, ','))
		exit_protocol(specs, 0, "Error in parse_vec_spec");
	ptr->x = ft_atof(input);
	advance(&input, specs);
	ptr->y = ft_atof(input);
	advance(&input, specs);
	ptr->z = ft_atof(input);
	*ptr = normalise(*ptr);
}

void			parse_vec_col(t_vec3 *ptr, char *input, t_rt *specs)
{
	if (!ft_strchr(input, ','))
		exit_protocol(specs, 0, "Error in parse_vec_spec");
	ptr->x = ft_atof(input);
	advance(&input, specs);
	ptr->y = ft_atof(input);
	advance(&input, specs);
	ptr->z = ft_atof(input);
	ptr->x = (ptr->x < 0) ? 0 : ptr->x;
	ptr->x = (ptr->x > 1) ? 1 : ptr->x;
	ptr->y = (ptr->y < 0) ? 0 : ptr->y;
	ptr->y = (ptr->y > 1) ? 1 : ptr->y;
	ptr->z = (ptr->z < 0) ? 0 : ptr->z;
	ptr->z = (ptr->z > 1) ? 1 : ptr->z;
}
