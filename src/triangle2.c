/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:51:56 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:51:58 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	find_np_triangle(t_ray *ray, t_triangle *tr)
{
	double magnitude;

	magnitude = mag(tr->n);
	ray->p[0] = ray->cam[0] + ray->closest_t * ray->vp[0];
	ray->p[1] = ray->cam[1] + ray->closest_t * ray->vp[1];
	ray->p[2] = ray->cam[2] + ray->closest_t * ray->vp[2];
	ray->n[0] = tr->n[0] / magnitude;
	ray->n[1] = tr->n[1] / magnitude;
	ray->n[2] = tr->n[2] / magnitude;
}

void	compute_color_triangle(t_ray *ray, t_objects *root, t_triangle *obj)
{
	ray->red = ray->i * tr_color_red(root, obj);
	ray->green = ray->i * tr_color_green(root, obj);
	ray->blue = ray->i * tr_color_blue(root, obj);
}

int		tr_color_red(t_objects *root, t_triangle *obj)
{
	int		color;
	t_light	*l;

	l = root->light;
	color = obj->color[0];
	if (root->ambient->i != 0)
		color = color + root->ambient->color[0];
	while (l != NULL)
	{
		if (l->i != 0)
			color = color + l->color[0];
		l = l->next;
	}
	if (color > 255)
		color = 255;
	return (color);
}

int		tr_color_green(t_objects *root, t_triangle *obj)
{
	int		color;
	t_light	*l;

	l = root->light;
	color = obj->color[1];
	if (root->ambient->i != 0)
		color = color + root->ambient->color[1];
	while (l != NULL)
	{
		if (l->i != 0)
			color = color + l->color[1];
		l = l->next;
	}
	if (color > 255)
		color = 255;
	return (color);
}

int		tr_color_blue(t_objects *root, t_triangle *obj)
{
	int		color;
	t_light	*l;

	l = root->light;
	color = obj->color[2];
	if (root->ambient->i != 0)
		color = color + root->ambient->color[2];
	while (l != NULL)
	{
		if (l->i != 0)
			color = color + l->color[2];
		l = l->next;
	}
	if (color > 255)
		color = 255;
	return (color);
}
