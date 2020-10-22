#include "minirt.h"

void cylinder_ray(t_ray *ray, t_objects *root)
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
		return ;
	find_np_cylinder(ray, cy);
	compute_lighting(root, ray);
	compute_color_cylinder(ray, root, cy);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void cylinder_closest(t_ray *ray, t_cylinder **cy, t_cylinder *temp)
{
	cylinder_intersec(ray, temp);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < ray->closest_t)
	{
		if(cylinder_limits(ray, temp))
		{
			ray->closest_t = ray->t1;
			*cy = temp;
		}
	}
	if ((ray->t2 >= ray->t_min && ray->t2 < ray->t_max) && ray->t2 < ray->closest_t)
	{
		if(cylinder_limits2(ray, temp))
		{
			ray->closest_t = ray->t2;
			*cy = temp;
		}
	}
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
	cy->d = dot_prod(y, y) - (cy->diam / 2) * (cy->diam / 2);
}

int cylinder_limits(t_ray *ray, t_cylinder *cy)
{
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
void compute_color_cylinder(t_ray *ray, t_objects *root, t_cylinder *obj)
{
	ray->red = ray->i * cy_color_red(root, obj);
	ray->green = ray->i * cy_color_green(root, obj);
	ray->blue = ray->i * cy_color_blue(root, obj);
}

int cy_color_red(t_objects *root, t_cylinder *obj)
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

int cy_color_green(t_objects *root, t_cylinder *obj)
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

int cy_color_blue(t_objects *root, t_cylinder *obj)
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