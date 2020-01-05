#include "rt.h"

static char		*putnum(char *name)
{
	static unsigned int	num;
	char				*tmp;
	char				*tmp1;

	if (num > 0)
	{
		tmp = name;
		name = ft_strjoin(name, "(");
		free(tmp);
		tmp = name;
		tmp1 = ft_itoa(num);
		name = ft_strjoin(name, tmp1);
		free(tmp);
		free(tmp1);
		tmp = name;
		name = ft_strjoin(name, ")");
		free(tmp);
	}
	num++;
	return (name);
}

static char		*extract_name(char *file_name)
{
	char	*name;
	char	*tmp;

	while (*file_name && *file_name != '/')
		file_name++;
	if (!(name = ft_strdup(file_name)))
		return (NULL);
	name = putnum(name);
	if (!(tmp = ft_strjoin("images_saved", name)))
	{
		free(name);
		return (NULL);
	}
	free(name);
	if (!(name = ft_strjoin(tmp, ".ppm")))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (name);
}

static void		set_title(FILE *fp)
{
	char	*str;
	char	*tmp;

	tmp = ft_itoa(W_IMG);
	str = ft_strjoin(tmp, " ");
	fwrite("P6\n", 1, 3, fp);
	fwrite(str, 1, ft_strlen_err(str), fp);
	free(str);
	free(tmp);
	tmp = ft_itoa(H_IMG);
	str = ft_strjoin(tmp, "\n");
	fwrite(str, 1, ft_strlen_err(str), fp);
	fwrite("255\n", 1, 4, fp);
	free(str);
	free(tmp);
}

void		fill_file(t_rt *specs, FILE *fp)
{
	unsigned char color[3];
	int		i;

	i = 0;
	set_title(fp);
	while (i < W_IMG * H_IMG * 4)
	{
		color[0] = specs->img_s->data[i + 2];
		color[1] = specs->img_s->data[i + 1];
		color[2] = specs->img_s->data[i];
		i += 4;
		fwrite(color, 1, 3, fp);
	}
}

void		save_file(t_rt *specs)
{
	FILE	*fp;
	char	*name;

	if (!(name = extract_name(specs->file_name)) ||
		!(fp = fopen(name, "wb")))
	{
		ft_putstr_fd("Error : failed to save image\n", 2);
		return ;
	}
	free(name);
	fill_file(specs, fp);
	mlx_string_put(specs->mlx, specs->win, 10, 10, RED, "image saved");
}