#include "minirt.h"

void		sphere_ray(t_ray *ray, t_sphere *sph, t_light *light)
{
	int check;

	check = 0;
	sphere_intersec(ray, sph);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < ray->closest_t)	
	{
		ray->closest_t = ray->t1;
		check = 1;
	}
	if ((ray->t2 >= ray->t_min && ray->t2 < ray->t_max) && ray->t2 < ray->closest_t)
	{
		ray->closest_t = ray->t2;
		check = 1;
	}
	if (check == 0)
		return ;
	find_np_sphere(ray, sph);
	compute_lighting(light, ray);
	compute_color_sphere(ray, light, sph);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void compute_color_sphere(t_ray *ray, t_light *light, t_sphere *obj)
{
	if (light->amb_i == 0)
	{
		ray->red = light->i * ((obj->color[0] + light->baran[0]) / 2);	
		ray->green = light->i * ((obj->color[1] + light->baran[1]) / 2);	
		ray->blue = light->i * ((obj->color[2] + light->baran[2]) / 2);	
	}
	else if (light->point_i == 0)
	{
		ray->red = light->i * ((obj->color[0] + light->osel[0]) / 2);	
		ray->green = light->i * ((obj->color[1] + light->osel[1]) / 2);	
		ray->blue = light->i * ((obj->color[2] + light->osel[2]) / 2);	
	}
	else
	{
		ray->red = light->i * ((obj->color[0] + light->baran[0] + light->osel[0]) / 3);	
		ray->green = light->i * ((obj->color[1] + light->baran[1] + light->osel[1]) / 3);	
		ray->blue = light->i * ((obj->color[2] + light->baran[2] + light->osel[2]) / 3);	
	}
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
	k3 = dot_prod(co, co) - sph->radius * sph->radius;
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
