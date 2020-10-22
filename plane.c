#include "minirt.h"

void plane_ray(t_ray *ray, t_objects *root)
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
		return ;
	find_np_plane(ray, pl);
	compute_lighting(root, ray);
	compute_color_plane(ray, root, pl);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void plane_closest(t_ray *ray, t_plane **pl, t_plane *temp)
{
	plane_intersec(ray, temp);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < ray->closest_t)
	{
		ray->closest_t = ray->t1;
		*pl = temp;
	}
}

void plane_intersec(t_ray *ray, t_plane *pl)
{
	double oc[3];
	double k1;
	double k2;

	oc[0] = pl->c[0] - ray->cam[0];
	oc[1] = pl->c[1] - ray->cam[1];
	oc[2] = pl->c[2] - ray->cam[2];
			
	k1 = dot_prod(oc, pl->n);
	k2 = dot_prod(ray->vp, pl->n);
	if (k2 == 0)
		ray->t1 = ray->t_max;
	else
		ray->t1 = k1 / k2;
}

void find_np_plane(t_ray *ray, t_plane *pl)
{
	double magnitude;

	magnitude = mag(pl->n);
	ray->p[0] = ray->cam[0] + ray->closest_t * ray->vp[0];
	ray->p[1] = ray->cam[1] + ray->closest_t * ray->vp[1];
	ray->p[2] = ray->cam[2] + ray->closest_t * ray->vp[2];
	ray->n[0] = pl->n[0] / magnitude;
	ray->n[1] = pl->n[1] / magnitude;
	ray->n[2] = pl->n[2] / magnitude;
}

void compute_color_plane(t_ray *ray, t_objects *root, t_plane *obj)
{
	ray->red = ray->i * pl_color_red(root, obj);
	ray->green = ray->i * pl_color_green(root, obj);
	ray->blue = ray->i * pl_color_blue(root, obj);
}

int pl_color_red(t_objects *root, t_plane *obj)
{
	int color;
	t_light *l;

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

int pl_color_green(t_objects *root, t_plane *obj)
{
	int color;
	t_light *l;

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

int pl_color_blue(t_objects *root, t_plane *obj)
{
	int color;
	t_light *l;

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
