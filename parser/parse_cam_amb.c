/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam_amb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:44:12 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:44:13 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parse_camera(char *line, t_objects *root)
{
	t_camera *cam;

	cam = (t_camera*)malloc(sizeof(t_camera));
	if (cam == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		free_root(root);
		exit(0);
	}
	if ((fill_camera(line, cam)) == -1)
	{
		write(1, "Error\nInvalid arguments in .rt file\n", 36);
		free_root(root);
		exit(0);
	}
	lst_addback_camera(&(root->camera), cam);
}

int		fill_camera(char *line, t_camera *cam)
{
	line = line + 1;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((coordinates(&line, cam->c)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((direction(&line, cam->n)) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((fov(&line, &(cam->fov))) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}

void	parse_ambient(char *line, t_objects *root)
{
	t_ambient *amb;

	amb = (t_ambient*)malloc(sizeof(t_ambient));
	if (amb == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		free_root(root);
		exit(0);
	}
	if ((fill_ambient(line, amb)) == -1)
	{
		write(1, "Error\nInvalid arguments in .rt file\n", 36);
		free_root(root);
		exit(0);
	}
	lst_addback_ambient(root, amb);
}

int		fill_ambient(char *line, t_ambient *amb)
{
	line = line + 1;
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((brightness(&line, &(amb->i))) == -1)
		return (-1);
	if ((skip_space(&line)) == -1)
		return (-1);
	if ((color(&line, amb->color)) == -1)
		return (-1);
	skip_space(&line);
	if (*line != '\0')
		return (-1);
	return (1);
}

int		fov(char **line, int *fov)
{
	*fov = atoi_rt(line);
	if (*fov < 0 || *fov > 180)
		return (-1);
	return (1);
}
