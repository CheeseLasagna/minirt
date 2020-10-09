#include "minirt.h"

void plane_ray(t_ray *ray, t_plane *pl, t_light *light)
{
	int check;

	check = 0;
	plane_intersec(ray, pl);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < ray->closest_t)
	{
		check = 1;
		ray->closest_t = ray->t1;
	}
	if (check == 0)
		return ;
	find_np_plane(ray, pl);
	compute_lighting(light, ray);
	compute_color_plane(ray, light, pl);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void plane_intersec(t_ray *ray, t_plane *pl)
{
	double oc[3];
	double k1;
	double k2;

	oc[0] = pl->x - ray->cam[0];
	oc[1] = pl->y - ray->cam[1];
	oc[2] = pl->z - ray->cam[2];
			
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


void compute_color_plane(t_ray *ray, t_light *light, t_plane *obj)
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
