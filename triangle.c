#include "minirt.h"

void triangle_ray(t_ray *ray, t_objects *root)
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
		return ;
	find_np_triangle(ray, tr);
	compute_lighting(root->ambient, root->light, ray);
	compute_color_triangle(ray, root, tr);
	ray->color = (ray->red << 16) + (ray->green << 8) + (ray->blue);
}

void triangle_closest(t_ray *ray, t_triangle **tr, t_triangle *temp)
{
	find_normal(temp);
	tplane_intersec(ray, temp);
	if ((ray->t1 >= ray->t_min && ray->t1 < ray->t_max) && ray->t1 < ray->closest_t)
	{
		temp->p[0] = ray->cam[0] + ray->t1 * ray->vp[0];  
		temp->p[1] = ray->cam[1] + ray->t1 * ray->vp[1];  
		temp->p[2] = ray->cam[2] + ray->t1 * ray->vp[2];  
		if (inside_triangle(ray, temp)) 
		{
			ray->closest_t = ray->t1;
			*tr = temp;
		}
	}
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
	double oc[3];

	oc[0] = tr->a[0] - ray->cam[0];
	oc[1] = tr->a[1] - ray->cam[1];
	oc[2] = tr->a[2] - ray->cam[2];
			
	double k1 = dot_prod(oc, tr->n);
	double k2 = dot_prod(ray->vp, tr->n);
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
	ray->p[0] = ray->cam[0] + ray->closest_t * ray->vp[0];
	ray->p[1] = ray->cam[1] + ray->closest_t * ray->vp[1];
	ray->p[2] = ray->cam[2] + ray->closest_t * ray->vp[2];
	ray->n[0] = tr->n[0] / magnitude;
	ray->n[1] = tr->n[1] / magnitude;
	ray->n[2] = tr->n[2] / magnitude;
}


void compute_color_triangle(t_ray *ray, t_objects *root, t_triangle *obj)
{
	t_ambient *amb;
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
	}
}
