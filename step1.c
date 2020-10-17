#include "minirt.h"

void render(t_image *img, t_ray *ray, t_objects *root)
{
	while (ray->x < img->img_x / 2)
	{
		while (ray->y < img->img_y / 2)
		{
			ray->closest_t = ray->t_max;
			ray->color = 0;
			viewport_xyz(img, ray, root);
			sphere_ray(ray, root);
			plane_ray(ray, root);
			//triangle_ray(ray, root);
			cylinder_ray(ray, root);
//			square_ray(ray, &sq);
			my_mlx_pixel_put(img, ray->x, ray->y, ray->color);
			ray->y++;
		}
		ray->x++;
		ray->y = img->img_y / -2;
	}
}

void viewport_xyz(t_image *img, t_ray *ray, t_objects *root)
{
	double magnitude;
	ray->vp[0] = ray->x * img->viewpoint_w / img->img_x + root->camera->n[0];
	ray->vp[1] = ray->y * img->viewpoint_h / img->img_y + root->camera->n[1];
	ray->vp[2] = img->d;
	//ray->vp[2] = 1;
	//printf("ray-vp = %f\n", ray->vp[2]);
}
