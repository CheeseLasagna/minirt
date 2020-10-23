#include "minirt.h"

void	compute_color_plane(t_ray *ray, t_objects *root, t_plane *obj)
{
	ray->red = ray->i * pl_color_red(root, obj);
	ray->green = ray->i * pl_color_green(root, obj);
	ray->blue = ray->i * pl_color_blue(root, obj);
}

int		pl_color_red(t_objects *root, t_plane *obj)
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

int		pl_color_green(t_objects *root, t_plane *obj)
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

int		pl_color_blue(t_objects *root, t_plane *obj)
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
