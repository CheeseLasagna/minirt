#include "minirt.h"

void		sphere_ray(t_ray *ray, t_objects *root)
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
		return ;
	find_np_sphere(ray, sph);
	compute_lighting(root, ray);
	compute_color_sphere(ray, root, sph);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void sphere_closest(t_ray *ray, t_sphere **sph, t_sphere *temp)
{
	sphere_intersec(ray, temp);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < ray->closest_t)	
	{
		ray->closest_t = ray->t1;
		*sph = temp;
	}
	if ((ray->t2 >= ray->t_min && ray->t2 < ray->t_max) && ray->t2 < ray->closest_t)
	{
		ray->closest_t = ray->t2;
		*sph = temp;
	}
}

void compute_color_sphere(t_ray *ray, t_objects *root, t_sphere *obj)
{
	ray->red = ray->i * sph_color_red(root, obj);
	ray->green = ray->i * sph_color_green(root, obj);
	ray->blue = ray->i * sph_color_blue(root, obj);
	/*t_ambient *amb;
	t_light *l;

	amb = root->ambient;
	l = root->light;
	if (amb->i == 0)
	{
		ray->red = ray->i * ((obj->color[0] + l->color[0]) / 2);	
		ray->green = ray->i * ((obj->color[1] + l->color[1]) / 2);	
		ray->blue = ray->i * ((obj->color[2] + l->color[2]) / 2);	
	}
	else if (l->i == 0)
	{
		ray->red = ray->i * ((obj->color[0] + amb->color[0]) / 2);	
		ray->green = ray->i * ((obj->color[1] + amb->color[1]) / 2);	
		ray->blue = ray->i * ((obj->color[2] + amb->color[2]) / 2);	
	}
	else
	{
		ray->red = ray->i * ((obj->color[0] + l->color[0] + amb->color[0]) / 3);	
		ray->green = ray->i * ((obj->color[1] + l->color[1] + amb->color[1]) / 3);	
		ray->blue = ray->i * ((obj->color[2] + l->color[2] + amb->color[2]) / 3);	
	}*/
}

int sph_color_red(t_objects *root, t_sphere *obj)
{
	int n;
	int color;
	t_light *l;

	n = 1;
	l = root->light;
	color = obj->color[0];
	if (root->ambient->i != 0)
	{
		color = color + root->ambient->color[0];
		n++;
	}
	while (l != NULL) 
	{
		if (l->i != 0)
		{
			color = color + l->color[0];
			n++;
		}
		l = l->next;
	}
	color = color / n;
	return (color);
}

int sph_color_green(t_objects *root, t_sphere *obj)
{
	int n;
	int color;
	t_light *l;

	n = 1;
	l = root->light;
	color = obj->color[1];
	if (root->ambient->i != 0)
	{
		color = color + root->ambient->color[1];
		n++;
	}
	while (l != NULL) 
	{
		if (l->i != 0)
		{
			color = color + l->color[1];
			n++;
		}
		l = l->next;
	}
	color = color / n;
	return (color);
}

int sph_color_blue(t_objects *root, t_sphere *obj)
{
	int n;
	int color;
	t_light *l;

	n = 1;
	l = root->light;
	color = obj->color[2];
	if (root->ambient->i != 0)
	{
		color = color + root->ambient->color[2];
		n++;
	}
	while (l != NULL) 
	{
		if (l->i != 0)
		{
			color = color + l->color[2];
			n++;
		}
		l = l->next;
	}
	color = color / n;
	return (color);
}

void sphere_intersec(t_ray *ray, t_sphere *sph)
{
	double co[3];
	double k1;
	double k2;
	double k3;
	double discriminant;

	co[0] = ray->cam[0] - sph->c[0];
	co[1] = ray->cam[1] - sph->c[1];
	co[2] = ray->cam[2] - sph->c[2];
	k1 = dot_prod(ray->vp, ray->vp);
	k2 = 2 * dot_prod(co, ray->vp);
	k3 = dot_prod(co, co) - (sph->diam / 2) * (sph->diam / 2);
	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
	{
		ray->t1 = ray->t_max;
		ray->t2 = ray->t_max;
	}
	else
	{
		ray->t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
		ray->t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
	}
}

void find_np_sphere(t_ray *ray, t_sphere *sph)
{
	double magnitude;
	
	ray->p[0] = ray->cam[0] + ray->closest_t * ray->vp[0];	
	ray->p[1] = ray->cam[1] + ray->closest_t * ray->vp[1];	
	ray->p[2] = ray->cam[2] + ray->closest_t * ray->vp[2];
	ray->n[0] = ray->p[0] - sph->c[0];
	ray->n[1] = ray->p[1] - sph->c[1];
	ray->n[2] = ray->p[2] - sph->c[2];
	magnitude = mag(ray->n);
	ray->n[0] = ray->n[0] / magnitude;	
	ray->n[1] = ray->n[1] / magnitude;	
	ray->n[2] = ray->n[2] / magnitude;	
}
