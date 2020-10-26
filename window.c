#include "minirt.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	x = img->img_x / 2 + x;
	y = img->img_y / 2 - y;
	dst = img->address + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	imgcam(t_image *img, t_ray *ray, t_objects *root)
{
	t_square *temp;

	temp = root->square;
	img->img_x = root->resol->r[0];
	img->img_y = root->resol->r[1];
	img->viewpoint_w = find_width(root->camera->fov);
	img->viewpoint_h = 1;
	img->d = 1;
	ray->cam[0] = root->camera->c[0];
	ray->cam[1] = root->camera->c[1];
	ray->cam[2] = root->camera->c[2];
	ray->t_min = 1;
	ray->t_max = 2147483647;
	ray->x = img->img_x / -2;
	ray->y = img->img_y / -2;
}

int		close_w(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->img->mlx, data->img->window);
		exit(0);
	}
	if (keycode == 65363)
	{
		if (data->root->camera->next != NULL)
		{
			data->root->camera = data->root->camera->next;
			push_new_img(data->img, data->ray, data->root);
		}
	}
	if (keycode == 65361)
	{
		if (data->root->camera->prev != NULL)
		{
			data->root->camera = data->root->camera->prev;
			push_new_img(data->img, data->ray, data->root);
		}
	}
}

void	push_new_img(t_image *img, t_ray *ray, t_objects *root)
{
	imgcam(img, ray, root);
	img->image = mlx_new_image(img->mlx, img->img_x, img->img_y);
	img->address = mlx_get_data_addr(img->image,
			&img->bits_per_pixel, &img->line_size, &img->endian);
	render(img, ray, root);
	mlx_put_image_to_window(img->mlx, img->window, img->image, 0, 0);
}

void	window_manage(t_objects *root)
{
	t_image	img;
	t_ray	ray;
	t_data	data;

	data.root = root;
	data.img = &img;
	data.ray = &ray;
	img.mlx = mlx_init();
	img.window = mlx_new_window(img.mlx, root->resol->r[0],
						root->resol->r[1], "Hello there");
	push_new_img(&img, &ray, root);
	mlx_hook(img.window, 2, 1L << 0, close_w, &data);
	mlx_hook(img.window, 17, 1L << 17, close_k, 0);
	mlx_loop(img.mlx);
	return ;
}
