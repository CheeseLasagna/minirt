#include "header.h"

void	parse_plane(char *line, t_objects *root)
{
	t_plane *pl;

	pl = (t_plane*)malloc(sizeof(t_plane));
	if (pl == NULL)
	{
		write(2, "no memory\n", 10);
		free_root(root);
		exit(EXIT_FAILURE);
	}
	if ((fill_plane(line, pl)) == -1)
	{
		write(2, "error in arguments\n", 19);
		free_root(root);
		exit(EXIT_FAILURE);
	}
	lst_addback_plane(&(root->plane), pl);
}

int		fill_plane(char *line, t_plane *pl)
{
	line = line + 2;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, pl->c)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((direction(&line, pl->n)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((color(&line, pl->color)) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}

void	parse_sphere(char *line, t_objects *root)
{
	t_sphere *sph;

	sph = (t_sphere*)malloc(sizeof(t_sphere));
	if (sph == NULL)
	{
		write(2, "no memory\n", 10);
		free_root(root);
		exit(EXIT_FAILURE);
	}
	if ((fill_sphere(line, sph)) == -1)
	{
		write(2, "error in arguments\n", 19);
		free_root(root);
		exit(EXIT_FAILURE);
	}
	lst_addback_sphere(&(root->sphere), sph);
}

int		fill_sphere(char *line, t_sphere *sph)
{
	line = line + 2;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, sph->c)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	side(&line, &(sph->diam));
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((color(&line, sph->color)) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}
