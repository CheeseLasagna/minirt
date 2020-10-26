#include "header.h"

void	parse_triangle(char *line, t_objects *root)
{
	t_triangle *tr;

	tr = (t_triangle*)malloc(sizeof(t_triangle));
	if (tr == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		free_root(root);
		exit(0);
	}
	if ((fill_triangle(line, tr)) == -1)
	{
		write(1, "Error\nInvalid arguments\n", 24);
		free_root(root);
		exit(0);
	}
	lst_addback_triangle(&(root->triangle), tr);
}

int		fill_triangle(char *line, t_triangle *tr)
{
	line = line + 2;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, tr->a)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, tr->b)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, tr->c)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((color(&line, tr->color)) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}

void	parse_light(char *line, t_objects *root)
{
	t_light *l;

	l = (t_light*)malloc(sizeof(t_light));
	if (l == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		free_root(root);
		exit(0);
	}
	if ((fill_light(line, l)) == -1)
	{
		write(1, "Error\nInvalid arguments\n", 24);
		free_root(root);
		exit(0);
	}
	lst_addback_light(&(root->light), l);
}

int		fill_light(char *line, t_light *l)
{
	line = line + 1;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, l->c)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((brightness(&line, &(l->i))) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((color(&line, l->color)) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}

int		brightness(char **line, double *i)
{
	*i = atoi_doub_rt(line);
	if (*i < 0 || *i > 1)
		return (-1);
	return (1);
}
