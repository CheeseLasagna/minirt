#include "minirt.h"

void	compute_lighting(t_objects *root, t_ray *ray)
{
	double l[3];
	double dot;
	t_light *light;

	light = root->light;
	ray->i = 0;
	if (root->ambient->i != 0)
		ray->i = ray->i + root->ambient->i;
	while (light != NULL)
	{
    	if (light->i != 0)
		{
			l[0] = light->c[0] - ray->p[0];	
			l[1] = light->c[1] - ray->p[1];	
			l[2] = light->c[2] - ray->p[2];
			if ((check_shadow(*ray, root, l)))
			{
				light = light->next;
				continue ;
			}
			dot = dot_prod(ray->n, l);
			if (dot > 0)
				ray->i += light->i * (dot / (mag(ray->n) * mag(l)));
		}
		light = light->next;
	}
	if (ray->i > 1)
		ray->i = 1;
}	

int check_shadow(t_ray ray, t_objects *root, double *l)
{
	ray.cam[0] = ray.p[0];
	ray.cam[1] = ray.p[1];
	ray.cam[2] = ray.p[2];
	ray.vp[0] = l[0];
	ray.vp[1] = l[1];
	ray.vp[2] = l[2];
	ray.t_min = 0.001;
	ray.t_max = 1;
	ray.closest_t = ray.t_max;
	if ((sphere_shadow(&ray, root)) == 1)
		return (1);
	if ((plane_shadow(&ray, root)) == 1)
		return (1);
	if ((cylinder_shadow(&ray, root)) == 1)
		return (1);
	if ((triangle_shadow(&ray, root)) == 1)
		return (1);
	if ((square_shadow(&ray, root)) == 1)
		return (1);
	return (0);
}

int sphere_shadow(t_ray *ray, t_objects *root)
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

int triangle_shadow(t_ray *ray, t_objects *root)
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

int plane_shadow(t_ray *ray, t_objects *root)
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

int cylinder_shadow(t_ray *ray, t_objects *root)
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

int square_shadow(t_ray *ray, t_objects *root)
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

void cross_prod(double *res, double *vec1, double *vec2)
{
	res[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];	
	res[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];	
	res[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];	
}

double dot_prod(double *vec1, double *vec2)
{
	double result;

	result = vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
	return (result);
}

double mag(double *vec)
{
    double x;

    x = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
    return (x);
}
