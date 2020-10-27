/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pl_sp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:44:20 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:44:21 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parse_plane(char *line, t_objects *root)
{
	t_plane *pl;

	pl = (t_plane*)malloc(sizeof(t_plane));
	if (pl == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		free_root(root);
		exit(0);
	}
	if ((fill_plane(line, pl)) == -1)
	{
		write(1, "Error\nInvalid arguments in .rt file\n", 36);
		free_root(root);
		exit(0);
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
		write(1, "Error\nno memory\n", 16);
		free_root(root);
		exit(0);
	}
	if ((fill_sphere(line, sph)) == -1)
	{
		write(1, "Error\nInvalid arguments in .rt file\n", 36);
		free_root(root);
		exit(0);
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
