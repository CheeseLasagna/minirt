#include "minirt.h"

void triangle_ray(t_ray *ray, t_triangle *tr, t_light *light)
{
	int check;

	check = 0;
	find_normal(tr);
	tplane_intersec(ray, tr);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < ray->closest_t)
	{
		tr->p[0] = ray->cam_x + ray->t1 * ray->vp_x;  
		tr->p[1] = ray->cam_y + ray->t1 * ray->vp_y;  
		tr->p[2] = ray->cam_z + ray->t1 * ray->vp_z;  
		if (inside_triangle(ray, tr)) 
		{
			check = 1;
			ray->closest_t = ray->t1;
		}
	}
	if (check == 0)
		return ;
	find_np_triangle(ray, tr);
	compute_lighting(light, ray);
	compute_color_triangle(ray, light, tr);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void find_normal(t_triangle *tr)
{
	double vec_ab[3];
	double vec_ac[3];

	vec_ab[0] = tr->b[0] - tr->a[0];
	vec_ab[1] = tr->b[1] - tr->a[1];
	vec_ab[2] = tr->b[2] - tr->a[2];
	vec_ac[0] = tr->c[0] - tr->a[0];
	vec_ac[1] = tr->c[1] - tr->a[1];
	vec_ac[2] = tr->c[2] - tr->a[2];
	cross_prod(tr->n, vec_ab, vec_ac);
}

void tplane_intersec(t_ray *ray, t_triangle *tr)
{
	double oc_x;
	double oc_y;
	double oc_z;

	oc_x = tr->a[0] - ray->cam_x;
	oc_y = tr->a[1] - ray->cam_y;
	oc_z = tr->a[2] - ray->cam_z;
			
	double k1 = oc_x * tr->n[0] + oc_y * tr->n[1] + oc_z * tr->n[2];
	double k2 = ray->vp_x * tr->n[0] + ray->vp_y * tr->n[1] + ray->vp_z * tr->n[2];
	if (k2 == 0)
		ray->t1 = ray->t_max;
	else
		ray->t1 = k1 / k2;
}

int inside_triangle(t_ray *ray, t_triangle *tr)
{
	int i;
	double testveca[3];
	double testvecb[3];
	double testvecc[3];

	i = 0;
	while (i < 3)
	{
		tr->vec_ab[i] =	tr->b[i] - tr->a[i]; 	
		tr->vec_bc[i] =	tr->c[i] - tr->b[i]; 	
		tr->vec_ca[i] =	tr->a[i] - tr->c[i]; 	
		tr->vec_ap[i] = tr->p[i] - tr->a[i];	
		tr->vec_bp[i] = tr->p[i] - tr->b[i];	
		tr->vec_cp[i] = tr->p[i] - tr->c[i];	
		i++;
	}
	cross_prod(testveca, tr->vec_ab, tr->vec_ap); 
	cross_prod(testvecb, tr->vec_bc, tr->vec_bp); 
	cross_prod(testvecc, tr->vec_ca, tr->vec_cp); 
	if ((dot_prod(testveca, tr->n)) < 0)
		return (0); 	
	if ((dot_prod(testvecb, tr->n)) < 0)
		return (0); 	
	if ((dot_prod(testvecc, tr->n)) < 0)
		return (0); 	
	return (1);
}

void find_np_triangle(t_ray *ray, t_triangle *tr)
{
	double magnitude;

	magnitude = mag(tr->n);
	ray->p[0] = ray->cam_x + ray->closest_t * ray->vp_x;
	ray->p[1] = ray->cam_y + ray->closest_t * ray->vp_y;
	ray->p[2] = ray->cam_z + ray->closest_t * ray->vp_z;
	ray->n[0] = tr->n[0] / magnitude;
	ray->n[1] = tr->n[1] / magnitude;
	ray->n[2] = tr->n[2] / magnitude;
}


void compute_color_triangle(t_ray *ray, t_light *light, t_triangle *obj)
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
