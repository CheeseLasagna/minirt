#include "minilibx/mlx.h"
#include <stdio.h>
#include <X11/X.h>
#include "minilibx/mlx_int.h"

typedef struct	s_image_data
{
	void *mlx;
	void *window;
	void *image;
	char *address;
	int bits_per_pixel;
	int line_size;
	int endian;
	int color;
}				t_image_data;

void	my_mlx_pixel_put(t_image_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->address + (y * data->line_size + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	main(void)
{
	t_image_data img;

	img.mlx = mlx_init();
	img.window = mlx_new_window(img.mlx, 1000, 700, "Hellooo");
	image = mlx_new_image(mlx, 1000, 700);
	img.address = mlx_get_data_addr(image, &img.bits_per_pixel, &img.line_size, &img.endian);
//	my_mlx_pixel_put(&img, 10, 10, 255);
//	mlx_destroy_image(mlx, image);
	mlx_loop_hook(img.mlx, loop_test, &img);
//	mlx_put_image_to_window(mlx, window, image, 0, 0);
//	printf("address %s\nbits %d\nsize_line %d\nendian %d\n", img.addr, img.bits, img.size_line, img.endian);
	mlx_loop(img.mlx);
	
	return (0);
}
	
