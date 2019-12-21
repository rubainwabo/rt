/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:35:54 by rkamegne          #+#    #+#             */
/*   Updated: 2019/12/09 19:52:07 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*readline(const int fd, char **str, int *ret1)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	char	*tmp;

	buff[0] = '\0';
	while (!ft_strchr(buff, '\n') && (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		tmp = str[fd];
		buff[ret] = '\0';
		str[fd] = ft_strjoin(str[fd], buff);
		ft_strdel(&tmp);
	}
	*ret1 = ret;
	return (str[fd]);
}

static int	free_static(int fd, char **str)
{
	free(str[fd]);
	return (-1);
}

int			get_next_line(const int fd, char **line)
{
	static char *str[OPEN_MAX];
	char		*tmp;
	int			i;
	int			ret1;

	if (fd < 0 || fd > OPEN_MAX || !line ||
			(!str[fd] && !(str[fd] = ft_strnew(0))))
		return (-1);
	if (!(str[fd] = readline(fd, str, &ret1)) || ret1 == -1)
		return (free_static(fd, str));
	if (!*(tmp = str[fd]))
	{
		ft_strdel(&str[fd]);
		return (0);
	}
	if ((i = (ft_strchr(str[fd], '\n') != 0)))
		*line = ft_strsub(str[fd], 0, ft_strchr(str[fd], '\n') - str[fd]);
	else
		*line = ft_strdup(str[fd]);
	str[fd] = ft_strsub(str[fd], (unsigned int)(ft_strlen_err(*line) + i),
			(size_t)(ft_strlen_err(str[fd]) - (ft_strlen_err(*line) + i)));
	ft_strdel(&tmp);
	if (ft_strlen_err(*line) || str[fd] != NULL)
		return (1);
	return (0);
}
