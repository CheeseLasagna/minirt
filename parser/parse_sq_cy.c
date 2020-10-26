#include "header.h"

void	parse_square(char *line, t_objects *root)
{
	t_square *sq;

	sq = (t_square*)malloc(sizeof(t_square));
	if (sq == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		free_root(root);
		exit(0);
	}
	if ((fill_square(line, sq)) == -1)
	{
		write(1, "Error\nInvalid arguments\n", 24);
		free_root(root);
		exit(0);
	}
	vert_zero(sq);
	lst_addback_square(&(root->square), sq);
}

void	vert_zero(t_square *sq)
{
	sq->check = 0;
	sq->p[0] = 0;
	sq->p[1] = 0;
	sq->p[2] = 0;
	sq->b[0] = 0;
	sq->b[1] = 0;
	sq->b[2] = 0;
	sq->d[0] = 0;
	sq->d[1] = 0;
	sq->d[2] = 0;
	sq->a[0] = 0;
	sq->a[1] = 0;
	sq->a[2] = 0;
	sq->e[0] = 0;
	sq->e[1] = 0;
	sq->e[2] = 0;
}

int		fill_square(char *line, t_square *sq)
{
	line = line + 2;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, sq->c)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((direction(&line, sq->n)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	side(&line, &(sq->side));
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((color(&line, sq->color)) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}

void	parse_cylinder(char *line, t_objects *root)
{
	t_cylinder *cy;

	cy = (t_cylinder*)malloc(sizeof(t_cylinder));
	if (cy == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		free_root(root);
		exit(0);
	}
	if ((fill_cylinder(line, cy)) == -1)
	{
		write(1, "Error\nInvalid arguments\n", 24);
		free_root(root);
		exit(0);
	}
	lst_addback_cylinder(&(root->cylinder), cy);
}

int		fill_cylinder(char *line, t_cylinder *cy)
{
	line = line + 2;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, cy->c)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((direction(&line, cy->n)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	side(&line, &(cy->diam));
	if ((skip_space(&line)) == -1)
		return (-1);
	side(&line, &(cy->height));
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((color(&line, cy->color)) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}
