#include "minirt.h"

void basic(t_image *ptr, t_ray *ray)
{
	t_sphere sphere;
	sphere.x = 0; 
	sphere.y = 0;
	sphere.z = 10;
	sphere.radius = 0.7; 
	sphere.color[0] = 0;
	sphere.color[1] = 100;
	sphere.color[2] = 255;
	ray->t_min = 1;
	ray->t_max = 2147483647;
	

	t_plane pl;
	pl.x = 0;
	pl.y = -3;
	pl.z = 5;
	pl.n_x = 0;
	pl.n_y = 1;
	pl.n_z = -0.1;
	pl.color[0] = 255;
	pl.color[1] = 0;
	pl.color[2] = 0;

	t_triangle tr;
	tr.a[0] = 2;
	tr.a[1] = 2;
	tr.a[2] = 15;
	tr.b[0] = 7;
	tr.b[1] = 1;
	tr.b[2] = 15;
	tr.c[0] = 5;
	tr.c[1] = 7;
	tr.c[2] = 15;
	tr.color[0] = 255;
	tr.color[1] = 0;
	tr.color[2] = 0;
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
			ptr->color = plane_ray(ray, &pl);
			ptr->color = triangle_ray(ray, &tr);
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
