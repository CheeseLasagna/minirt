/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:43:33 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:43:43 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parse_line(char *line, t_objects *root)
{
	if (line[0] == '\0')
		return ;
	if (line[0] == 'R' && line[1] == ' ')
		parse_resol(line, root);
	else if (line[0] == 'A' && line[1] == ' ')
		parse_ambient(line, root);
	else if (line[0] == 'c' && line[1] == ' ')
		parse_camera(line, root);
	else if (line[0] == 'l' && line[1] == ' ')
		parse_light(line, root);
	else if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		parse_plane(line, root);
	else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		parse_sphere(line, root);
	else if (line[0] == 's' && line[1] == 'q' && line[2] == ' ')
		parse_square(line, root);
	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		parse_cylinder(line, root);
	else if (line[0] == 't' && line[1] == 'r' && line[2] == ' ')
		parse_triangle(line, root);
	else
		parse_line2(root);
}

void	parse_line2(t_objects *root)
{
	write(1, "Error\nInvalid arguments in .rt file\n", 36);
	free_root(root);
	exit(0);
}
