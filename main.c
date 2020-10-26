#include "minirt.h"

void print_bmp(t_objects *root)
{
	t_image img;
	t_ray ray;
	t_data data;

	data.root = root;
	data.img = &img;
	data.ray = &ray;
	img.mlx = mlx_init();
	imgcam(&img, &ray, root);
	img.image = mlx_new_image(img.mlx, img.img_x, img.img_y);
	img.address = mlx_get_data_addr(img.image,
			&img.bits_per_pixel, &img.line_size, &img.endian);
	render(&img, &ray, root);
	save_bmp(&data);
}

void	save_bmp(t_data *data)
{
	int fd;
	t_bmp bmp;

	if ((fd = open("shot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0)
	{
		write(1, "failed to create file\n", 22);
		free_root(data->root);
	}
	//write_bmp_header(data, fd);
	//write_bmp_info(data, fd);
	//write_bmp_image(data, fd);
	bmp_vars_input(&bmp, data);
	bmp_write(bmp, data, fd);
	close(fd);
}

static void		bmp_vars_input(t_bmp *bmp, t_data *data)
{
	bmp->bftype[0] = 'B';
	bmp->bftype[1] = 'M';
	bmp->bfsize = 54 + 4 * (data->img->img_x * data->img->img_y);
	bmp->bfreserved1 = 0;
	bmp->bfreserved2 = 0;
	bmp->bfoffbits = 54;
	bmp->bisize = 40;
	bmp->biwidth = data->img->img_x;
	bmp->biheight = data->img->img_y;
	bmp->bicompression = 0;
	bmp->bisizeimage = 4 * data->img->img_y * data->img->img_y;
	bmp->bixpelspermeter = 0;
	bmp->biypelspermeter = 0;
	bmp->biclrused = 0;
	bmp->biclrimportant = 0;
	bmp->biplanes = 1;
	bmp->bibitcount = 32;
}

static void		bmp_write(t_bmp bmp, t_data *data, int fd)
{
	write(fd, &bmp.bftype, 2);
	write(fd, &bmp.bfsize, 4);
	write(fd, &bmp.bfreserved1, 2);
	write(fd, &bmp.bfreserved2, 2);
	write(fd, &bmp.bfoffbits, 4);
	write(fd, &bmp.bisize, 4);
	write(fd, &bmp.biwidth, 4);
	write(fd, &bmp.biheight, 4);
	write(fd, &bmp.biplanes, 2);
	write(fd, &bmp.bibitcount, 2);
	write(fd, &bmp.bicompression, 4);
	write(fd, &bmp.bisizeimage, 4);
	write(fd, &bmp.bixpelspermeter, 4);
	write(fd, &bmp.biypelspermeter, 4);
	write(fd, &bmp.biclrused, 4);
	write(fd, &bmp.biclrimportant, 4);
	draw_img(data, &bmp, fd);
}
//dst = img->address + (y * img->line_size + x * (img->bits_per_pixel / 8));

static void		draw_img(t_data *data, t_bmp *bmp, int fd)
{
	int x;
	int y;
	int *img;

	y = 0;
	img = malloc(sizeof(int) * bmp->biheight * bmp->biwidth);
	while (y < bmp->biheight)
	{
		x = 0;
		while (x < bmp->biwidth)
		{
			img[y * bmp->biwidth + x] = *(int*)(data->img->address + ((bmp->biheight - y) * data->img->line_size + x * (data->img->bits_per_pixel / 8)));
			x++;
		}
		y++;
	}
	write(fd, img, bmp->bisizeimage);
	free(img);
}

/*static void	write_bmp_header(t_data *data, int fd)
{
	int				i;
	unsigned char	header[14];

	i = 0;
	while (i < 14)
		header[i++] = (unsigned char)0;
	header[0] = (unsigned char)66;
	header[1] = (unsigned char)77;
	i = data->img->img_x * data->img->img_y * 4 + 54;
	header[2] = (unsigned char)(i % 256);
	header[3] = (unsigned char)(i / 256 % 256);
	header[4] = (unsigned char)(i / 256 / 256 % 256);
	header[5] = (unsigned char)(i / 256 / 256 / 256);
	header[10] = (unsigned char)54;
	write(fd, header, 14);
}

static void	write_bmp_info(t_data *data, int fd)
{
	int				i;
	unsigned char	header[40];

	i = 0;
	while (i < 40)
		header[i++] = (unsigned char)0;
	header[0] = (unsigned char)40;
	i = data->img->img_x;
	header[4] = (unsigned char)(i % 256);
	header[5] = (unsigned char)(i / 256 % 256);
	header[6] = (unsigned char)(i / 256 / 256 % 256);
	header[7] = (unsigned char)(i / 256 / 256 / 256);
	i = data->img->img_y;
	header[8] = (unsigned char)(i % 256);
	header[9] = (unsigned char)(i / 256 % 256);
	header[10] = (unsigned char)(i / 256 / 256 % 256);
	header[11] = (unsigned char)(i / 256 / 256 / 256);
	header[12] = (unsigned char)1;
	header[14] = (unsigned char)32;
	write(fd, header, 40);
}

static void	write_bmp_image(t_data *data, int fd)
{
	int				i;
	int				j;
	unsigned char	buff[4];

	i = data->img->img_x * (data->img->img_y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < data->img->img_x)
		{
			buff[0] = (unsigned char)(data->img->address[i] % 256);
			buff[1] = (unsigned char)(data->img->address[i] / 256 % 256);
			buff[2] = (unsigned char)(data->img->address[i] / 256 / 256 % 256);
			buff[3] = (unsigned char)0;
			write(fd, buff, 4);
			i++;
			j++;
		}
		i -= 2 * data->img->img_x;
	}
}*/

int		main(int argc, char **argv)
{
	int check;
	t_objects *root;

	check = arg_check(argc, argv);
	if((root = (t_objects*)malloc(sizeof(t_objects))) == NULL)
	{
		write(1, "malloc error\n", 13);
		exit(0);
	}
	open_read(argc, argv, root);
	if (!check)
		window_manage(root);
	else
		print_bmp(root);
	return (0);
}
