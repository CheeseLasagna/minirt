#include "minirt.h"

void	compute_lighting(t_light *light, t_ray *ray)
{
	double l[3];
	double dot;

	light->i = 0;
	if (light->amb_i != 0)
		light->i = light->i + light->amb_i;
    if (light->point_i != 0)
	{
		l[0] = light->pos[0] - ray->p[0];	
		l[1] = light->pos[1] - ray->p[1];	
		l[2] = light->pos[2] - ray->p[2];	
		dot = dot_prod(ray->n, l);
		//printf("dot = %f\n", dot);
		if (dot > 0)
			light->i += light->point_i * (dot / (mag(ray->n) * mag(l)));
	}
	if (light->i > 1)
		light->i = 1;
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
