/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:50:55 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:50:58 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sphere_shadow(t_ray *ray, t_objects *root)
{
	t_sphere *sph;
	t_sphere *temp;

	sph = NULL;
	temp = root->sphere;
	while (temp != NULL)
	{
		sphere_closest(ray, &sph, temp);
		temp = temp->next;
	}
	if (sph == NULL)
		return (0);
	return (1);
}

int	triangle_shadow(t_ray *ray, t_objects *root)
{
	t_triangle *tr;
	t_triangle *temp;

	tr = NULL;
	temp = root->triangle;
	while (temp != NULL)
	{
		triangle_closest(ray, &tr, temp);
		temp = temp->next;
	}
	if (tr == NULL)
		return (0);
	return (1);
}

int	plane_shadow(t_ray *ray, t_objects *root)
{
	t_plane *pl;
	t_plane *temp;

	pl = NULL;
	temp = root->plane;
	while (temp != NULL)
	{
		plane_closest(ray, &pl, temp);
		temp = temp->next;
	}
	if (pl == NULL)
		return (0);
	return (1);
}

int	cylinder_shadow(t_ray *ray, t_objects *root)
{
	t_cylinder *cy;
	t_cylinder *temp;

	cy = NULL;
	temp = root->cylinder;
	while (temp != NULL)
	{
		cylinder_closest(ray, &cy, temp);
		temp = temp->next;
	}
	if (cy == NULL)
		return (0);
	return (1);
}

int	square_shadow(t_ray *ray, t_objects *root)
{
	t_square *sq;
	t_square *temp;

	sq = NULL;
	temp = root->square;
	while (temp != NULL)
	{
		square_closest(ray, &sq, temp);
		temp = temp->next;
	}
	if (sq == NULL)
		return (0);
	return (1);
}
