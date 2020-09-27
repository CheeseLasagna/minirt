#include "minirt.h"

void	my_mlx_pixel_put(t_image_data *ptr, int x, int y, int color)
{
    char    *dst;

	x = ptr->res_x / 2 + x;
	y = ptr->res_y / 2 - y;
    dst = ptr->address + (y * ptr->line_size + x * (ptr->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

/*void test(t_image_data *ptr)
{
	int x = 200;
	int y = -100;

	if (x >= (ptr->res_x * -1 / 2) && x <= (ptr->res_x * 1 / 2))
	{
		if (y >= (ptr->res_y * -1 / 2) && y <= (ptr->res_y * 1 / 2))
		{
			x = ptr->res_x / 2 + x;
			y = ptr->res_y / 2 - y;
			my_mlx_pixel_put(ptr, x, y, 255<<8);
		}
	}
}*/

int	main(void)
{
	t_image_data img;
	t_ray_data ray;

	img.res_x = 700;
	img.res_y = 700;
	img.viewpoint_w = 700;
	img.viewpoint_h = 700;
	img.d = 600;
	ray.cam_x = 0;
	ray.cam_y = 0;
	ray.cam_z = 0;

	img.mlx = mlx_init();
	img.window = mlx_new_window(img.mlx, 1000, 700, "Hellooo");
	img.image = mlx_new_image(img.mlx, img.res_x, img.res_y);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.line_size, &img.endian);
//	mlx_destroy_image(mlx, image);
//	mlx_loop_hook(img.mlx, loop_test, &img);
//	test(&img);
	basic(&img, &ray);
	mlx_put_image_to_window(img.mlx, img.window, img.image, 0, 0);
	mlx_loop(img.mlx);
	
	return (0);
}
	
