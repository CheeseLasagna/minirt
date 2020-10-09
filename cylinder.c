#include "minirt.h"

void cylinder_ray(t_ray *ray, t_cylinder *cy, t_light *light)
{
	int check;

	check = 0;
	cylinder_intersec(ray, cy);
	closest_t_cyl(ray, cy, &check);
	find_np_cylinder(ray, cy);
	compute_lighting(light, ray);
	compute_color_cylinder(ray, light, cy);
	if (check == 0)
		return ;
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void find_np_cylinder(t_ray *ray, t_cylinder *cy)
{
	double magnitude;

	ray->p[0] = ray->cam[0] + ray->closest_t * ray->vp[0];
	ray->p[1] = ray->cam[1] + ray->closest_t * ray->vp[1];
	ray->p[2] = ray->cam[2] + ray->closest_t * ray->vp[2];
	ray->n[0] = ray->p[0] - (cy->c[0] + cy->m * cy->n[0]);
	ray->n[1] = ray->p[1] - (cy->c[1] + cy->m * cy->n[1]);
	ray->n[2] = ray->p[2] - (cy->c[2] + cy->m * cy->n[2]);
	magnitude = mag(ray->n);
	ray->n[0] = ray->n[0] / magnitude;
	ray->n[1] = ray->n[1] / magnitude;
	ray->n[2] = ray->n[2] / magnitude;
}

void compute_color_cylinder(t_ray *ray, t_light *light, t_cylinder *obj)
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

void closest_t_cyl(t_ray *ray, t_cylinder *cy, int *check)
{
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < ray->closest_t)
	{
		if(cylinder_limits(ray, cy))
		{
			ray->closest_t = ray->t1;
			*check = 1;
		}
	}
	if ((ray->t2 >= ray->t_min && ray->t2 < ray->t_max) && ray->t2 < ray->closest_t)
	{
		if(cylinder_limits2(ray, cy))
		{
			ray->closest_t = ray->t2;
			*check = 1;
		}
	}
}
	
void cylinder_intersec(t_ray *ray, t_cylinder *cy)
{
	double a;
	double b;
	double c;
	double discriminant;

	discriminant = mag(cy->n);
	cy->n[0] = cy->n[0] / discriminant;
	cy->n[1] = cy->n[1] / discriminant;
	cy->n[2] = cy->n[2] / discriminant;
	calc_cyl_abc(ray, cy);
	a = cy->a;
	b = cy->b;
	c = cy->d;
	discriminant = b * b - 4 * a * c;	
	if (discriminant < 0)
	{
		ray->t1 = ray->t_max;
		ray->t2 = ray->t_max;
	}
	else
	{
		ray->t1 = (-b + sqrt(discriminant)) / (2 * a);
		ray->t2 = (-b - sqrt(discriminant)) / (2 * a);
	}
}

void calc_cyl_abc(t_ray *ray, t_cylinder *cy)
{
	double x[3];
	double y[3];
	double dp[3];

	x[0] = ray->vp[0] - dot_prod(ray->vp, cy->n) * cy->n[0];
	x[1] = ray->vp[1] - dot_prod(ray->vp, cy->n) * cy->n[1];
	x[2] = ray->vp[2] - dot_prod(ray->vp, cy->n) * cy->n[2];
	dp[0] = ray->cam[0] - cy->c[0];	
	dp[1] = ray->cam[1] - cy->c[1];	
	dp[2] = ray->cam[2] - cy->c[2];	
	y[0] = dp[0] - dot_prod(dp, cy->n) * cy->n[0];
	y[1] = dp[1] - dot_prod(dp, cy->n) * cy->n[1];
	y[2] = dp[2] - dot_prod(dp, cy->n) * cy->n[2];
	cy->a = dot_prod(x, x);
	cy->b = 2 * dot_prod(x, y);
	cy->d = dot_prod(y, y) - cy->radius * cy->radius;
}

int cylinder_limits(t_ray *ray, t_cylinder *cy)
{
	double magni;
	double cp[3];

	cy->p[0] = ray->cam[0] + ray->t1 * ray->vp[0];	
	cy->p[1] = ray->cam[1] + ray->t1 * ray->vp[1];	
	cy->p[2] = ray->cam[2] + ray->t1 * ray->vp[2];	
	cp[0] = cy->p[0] - cy->c[0];
	cp[1] = cy->p[1] - cy->c[1];
	cp[2] = cy->p[2] - cy->c[2];
	cy->m = dot_prod(cp, cy->n) / dot_prod(cy->n, cy->n);	
	if (cy->m >= 0 && cy->m <= cy->height)
		return (1);
	return (0);
}

int cylinder_limits2(t_ray *ray, t_cylinder *cy)
{
	double magni;
	double cp[3];

	cy->p[0] = ray->cam[0] + ray->t2 * ray->vp[0];	
	cy->p[1] = ray->cam[1] + ray->t2 * ray->vp[1];	
	cy->p[2] = ray->cam[2] + ray->t2 * ray->vp[2];	
	cp[0] = cy->p[0] - cy->c[0];
	cp[1] = cy->p[1] - cy->c[1];
	cp[2] = cy->p[2] - cy->c[2];
	cy->m = dot_prod(cp, cy->n) / dot_prod(cy->n, cy->n);	
	if (cy->m >= 0 && cy->m <= cy->height)
		return (1);
	return (0);
}
