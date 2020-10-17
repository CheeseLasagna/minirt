#include "minirt.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char    *dst;

	x = img->img_x / 2 + x;
	y = img->img_y / 2 - y;
    dst = img->address + (y * img->line_size + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void imgcam(t_image *img, t_ray *ray, t_objects *root)
{
	img->img_x = root->resol->r[0];
	img->img_y = root->resol->r[1];
	img->viewpoint_w = 1;
	img->viewpoint_h = 1;
	img->d = root->camera->n[2];
	ray->cam[0] = root->camera->c[0];
	ray->cam[1] = root->camera->c[1];
	ray->cam[2] = root->camera->c[2];
	ray->t_min = 1;
	ray->t_max = 2147483647;
	ray->x = img->img_x / -2;
	ray->y = img->img_y / -2;
}

void	window_manage(t_objects *root)
{
	t_image img;
	t_ray ray;

	imgcam(&img, &ray, root);
	img.mlx = mlx_init();
	img.window = mlx_new_window(img.mlx, img.img_x, img.img_y, "Hello there");
	img.image = mlx_new_image(img.mlx, img.img_x, img.img_y);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.line_size, &img.endian);
//	mlx_destroy_image(mlx, image);
	render(&img, &ray, root);
	mlx_put_image_to_window(img.mlx, img.window, img.image, 0, 0);
	mlx_loop(img.mlx);
	
	return ;
}