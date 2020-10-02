#include "minirt.h"

void basic(t_image *ptr, t_ray *ray)
{
	t_sphere sphere;
	sphere.x = -5; 
	sphere.y = 5;
	sphere.z = 20;
	sphere.radius = 1; 
	sphere.color[0]= 0;
	sphere.color[1] = 100;
	sphere.color[2] = 255;
	ray->t_min = 1;
	ray->t_max = 2147483647;
	
	int x;
	int y;

	x = ptr->img_x / -2;
	y = ptr->img_y / -2;

	while (x < ptr->img_x / 2)
	{
		while (y < ptr->img_y / 2)
		{
			viewport_xyz(ptr, ray, x, y);
			ptr->color = sphere_ray(ray, &sphere);
			my_mlx_pixel_put(ptr, x, y, ptr->color);
			y++;
		}
		x++;
		y = ptr->img_y / -2;
	}
}

void viewport_xyz(t_image *ptr, t_ray *ray, int x, int y)
{
	ray->vp_x = x * ptr->viewpoint_w / ptr->img_x;
	ray->vp_y = y * ptr->viewpoint_h / ptr->img_y;
	ray->vp_z = ptr->d;
}
