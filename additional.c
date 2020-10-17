#include "minirt.h"

void	compute_lighting(t_ambient *amb, t_light *light, t_ray *ray)
{
	double l[3];
	double dot;

	ray->i = 0;
	if (amb->i != 0)
		ray->i = ray->i + amb->i;
    if (light->i != 0)
	{
		l[0] = light->c[0] - ray->p[0];	
		l[1] = light->c[1] - ray->p[1];	
		l[2] = light->c[2] - ray->p[2];	
		dot = dot_prod(ray->n, l);
		if (dot > 0)
			ray->i += light->i * (dot / (mag(ray->n) * mag(l)));
	}
	if (ray->i > 1)
		ray->i = 1;
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
