#include "minirt.h"

void	my_mlx_pixel_put(t_image *ptr, int x, int y, int color)
{
    char    *dst;

	x = ptr->img_x / 2 + x;
	y = ptr->img_y / 2 - y;
    dst = ptr->address + (y * ptr->line_size + x * (ptr->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void imgcam(t_image *ptr, t_ray *ray)
{
	ptr->img_x = 700;
	ptr->img_y = 700;
	ptr->viewpoint_w = 1;
	ptr->viewpoint_h = 1;
	ptr->d = 1;
	ray->cam_x = 0;
	ray->cam_y = 0;
	ray->cam_z = 0;
}

int	main(void)
{
	t_image img;
	t_ray ray;

	imgcam(&img, &ray);
	img.mlx = mlx_init();
	img.window = mlx_new_window(img.mlx, 700, 700, "Hellooo");
	img.image = mlx_new_image(img.mlx, img.img_x, img.img_y);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.line_size, &img.endian);
//	mlx_destroy_image(mlx, image);
	basic(&img, &ray)
	mlx_put_image_to_window(img.mlx, img.window, img.image, 0, 0);
	mlx_loop(img.mlx);
	
	return (0);
}
