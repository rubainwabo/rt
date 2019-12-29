#include "rtv1.h"

char		*extract_name(char *file_name)
{
	char	*name;
	char	*tmp;

	while (*file_name && *file_name != '/')
		file_name++;
	if (!(name = ft_strdup(file_name)))
		return (NULL);
	if (!(tmp = ft_strjoin("save_images", name)))
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

void		fill_file(t_rt *specs, FILE *fp)
{
	unsigned char color[3];
	int		i;

	i = 0;
	fprintf(fp, "P6\n%d %d\n255\n", W_IMG, H_IMG);
	while (i < W_IMG * H_IMG * 4)
	{
		color[0] = specs->img_str2[i + 2];
		color[1] = specs->img_str2[i + 1];
		color[2] = specs->img_str2[i];
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
	ft_putstr_fd("Image saved in the folder save_images\n", 2);
}