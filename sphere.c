#include "minirt.h"

void basic(t_image_data *ptr, t_ray_data *ptrray)
{
	int x;
	int y;

	x = ptr->res_x / -2;
	y = ptr->res_y / -2;

//	ptr->d = 700;
//	ptr->viewpoint_w = 700;
//	ptr->viewpoint-H = 700;

	while (x <= ptr->res_x / 2)
	{
		while (y <= ptr->res_y / 2)
		{
			canvas_to_viewport(ptr, ptrray, x, y);
			ptr->color = trace_ray(ptrray, 1, 10000000);
			my_mlx_pixel_put(ptr, x, y, ptr->color);
			y++;
		}
		x++;
		y = ptr->res_y / -2;
	}
}

void canvas_to_viewport(t_image_data *ptr, t_ray_data *ptrray, int x, int y)
{
	ptrray->vp_intersec_x = x * ptr->viewpoint_w / ptr->res_x;
	ptrray->vp_intersec_y = y * ptr->viewpoint_h / ptr->res_y;
	ptrray->vp_intersec_z = ptr->d;
}

int	trace_ray(t_ray_data *ptr, int t_min, int t_max)
{
	t_sphere_data sphere;
	sphere.x = 0;
	sphere.y = 0;
	sphere.z = 300;
	sphere.radius = 50;
	sphere.red = 255;
	sphere.green = 0;
	sphere.blue = 0;

	t_sphere_data *ptrsph;
	int closest_t = t_max;
	int color;

	ptrsph = NULL;
	intersect_sphere(ptr, &sphere);
	if ((ptr->t1 >= t_min && ptr->t1 < t_max) && ptr->t1 < closest_t)	
	{
		closest_t = ptr->t1;
		ptrsph = &sphere;
	}
	if ((ptr->t2 >= t_min && ptr->t2 < t_max) && ptr->t2 < closest_t)
	{
		closest_t = ptr->t2;
		ptrsph = &sphere;
	}	
	if (ptrsph == NULL)
		return (0);
	color = sphere.red << 16 + sphere.green << 8 + sphere.blue;
	return (color);	
}

void intersect_sphere(t_ray_data *ptrray, t_sphere_data *ptrsph)
{
	int oc_x = ptrray->cam_x - ptrsph->x;
	int oc_y = ptrray->cam_y - ptrsph->y;
	int oc_z = ptrray->cam_z - ptrsph->z;

	int k1 = ptrray->vp_intersec_x * ptrray->vp_intersec_x + ptrray->vp_intersec_y * ptrray->vp_intersec_y + ptrray->vp_intersec_z * ptrray->vp_intersec_z;
	int k2 = 2 * (oc_x * ptrray->vp_intersec_x + oc_y * ptrray->vp_intersec_y + oc_z * ptrray->vp_intersec_z);
	int k3 = (oc_x * oc_x + oc_y * oc_y + oc_z * oc_z) - ptrsph->radius * ptrsph->radius;

	int discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
	{
		ptrray->t1 = 10000000;
		ptrray->t2 = 10000000;
	}
	else
	{
		ptrray->t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
		ptrray->t1 = (-k2 - sqrt(discriminant)) / (2 * k1);
	}
}
