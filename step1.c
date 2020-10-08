#include "minirt.h"

void basic(t_image *ptr, t_ray *ray)
{
	t_sphere sphere;
	sphere.c[0] = 0; 
	sphere.c[1] = -2;
	sphere.c[2] = 15;
	sphere.radius = 2; 
	sphere.color[0] = 255;
	sphere.color[1] = 0;
	sphere.color[2] = 0;
	ray->t_min = 1;
	ray->t_max = 2147483647;

	t_plane pl;
	pl.x = 0;
	pl.y = -3.2;
	pl.z = 0;
	pl.n[0] = 0;
	pl.n[1] = 1;
	pl.n[2] = 0;
	pl.color[0] = 0;
	pl.color[1] = 10;
	pl.color[2] = 255;

	t_triangle tr;
	tr.a[0] = 1;
	tr.a[1] = -2;
	tr.a[2] = 14;
	tr.c[0] = 5;
	tr.c[1] = 0;
	tr.c[2] = 14;
	tr.b[0] = 3;
	tr.b[1] = 4;
	tr.b[2] = 14;
	tr.color[0] = 255;
	tr.color[1] = 0;
	tr.color[2] = 0;
	
	t_square sq;
	sq.a[0] = 1;
	sq.a[1] = 1;
	sq.a[2] = 5;
	sq.b[0] = 5;
	sq.b[1] = 1;
	sq.b[2] = 5;
	sq.c[0] = 1;
	sq.c[1] = 5;
	sq.c[2] = 5;
	sq.n[0] = 0;
	sq.n[1] = 0;
	sq.n[2] = -1;
	sq.color[0] = 255;
	sq.color[1] = 0;
	sq.color[2] = 0;

	t_cylinder cy;
	cy.c[0] = 1;
	cy.c[1] = 0.5;
	cy.c[2] = 7;
	cy.radius = 0.7;
	cy.color[0] = 255;
	cy.color[1] = 0;
	cy.color[2] = 0;

	t_light light;
	light.amb_i = 0;
	light.osel[0] = 0;
	light.osel[1] = 0;
	light.osel[2] = 50;
	light.baran[0] = 150;
	light.baran[1] = 0;
	light.baran[2] = 200;
	light.point_i = 0.5;
	light.pos[0] = -10;
	light.pos[1] = 0;
	light.pos[2] = 0;

	int x;
	int y;

	x = ptr->img_x / -2;
	y = ptr->img_y / -2;

	while (x < ptr->img_x / 2)
	{
		while (y < ptr->img_y / 2)
		{
			ray->closest_t = ray->t_max;
			ray->color = 0;
			viewport_xyz(ptr, ray, x, y);
			sphere_ray(ray, &sphere, &light);
			plane_ray(ray, &pl, &light);
			triangle_ray(ray, &tr, &light);
			my_mlx_pixel_put(ptr, x, y, ray->color);
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
