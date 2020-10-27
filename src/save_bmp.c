/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:51:18 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:51:19 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_bmp(t_objects *root)
{
	t_image	img;
	t_ray	ray;
	t_data	data;

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
	int		fd;
	t_bmp	bmp;

	if ((fd = open("shot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU
										| S_IRGRP | S_IROTH)) < 0)
	{
		write(1, "failed to create file\n", 22);
		free_root(data->root);
	}
	bmp_vars_input(&bmp, data);
	bmp_write(bmp, data, fd);
	close(fd);
}

void	bmp_vars_input(t_bmp *bmp, t_data *data)
{
	bmp->type[0] = 'B';
	bmp->type[1] = 'M';
	bmp->bfsize = 54 + 4 * (data->img->img_x * data->img->img_y);
	bmp->reserved1 = 0;
	bmp->reserved2 = 0;
	bmp->biplanes = 1;
	bmp->bibitcount = 32;
	bmp->bfoffbits = 54;
	bmp->bisize = 40;
	bmp->width = data->img->img_x;
	bmp->height = data->img->img_y;
	bmp->compression = 0;
	bmp->sizeimage = 4 * data->img->img_y * data->img->img_x;
	bmp->bixpelspermeter = 0;
	bmp->biypelspermeter = 0;
	bmp->biclrused = 0;
	bmp->biclrimportant = 0;
}

void	bmp_write(t_bmp bmp, t_data *data, int fd)
{
	write(fd, &bmp.type, 2);
	write(fd, &bmp.bfsize, 4);
	write(fd, &bmp.reserved1, 2);
	write(fd, &bmp.reserved2, 2);
	write(fd, &bmp.bfoffbits, 4);
	write(fd, &bmp.bisize, 4);
	write(fd, &bmp.width, 4);
	write(fd, &bmp.height, 4);
	write(fd, &bmp.biplanes, 2);
	write(fd, &bmp.bibitcount, 2);
	write(fd, &bmp.compression, 4);
	write(fd, &bmp.sizeimage, 4);
	write(fd, &bmp.bixpelspermeter, 4);
	write(fd, &bmp.biypelspermeter, 4);
	write(fd, &bmp.biclrused, 4);
	write(fd, &bmp.biclrimportant, 4);
	draw_img(data, &bmp, fd);
}

void	draw_img(t_data *data, t_bmp *bmp, int fd)
{
	int x;
	int y;
	int *img;

	y = 0;
	if ((img = malloc(sizeof(int) * bmp->height * bmp->width)) == NULL)
	{
		write(1, "Error\nno memory\n", 16);
		free_root(data->root);
		exit(0);
	}
	while (y < bmp->height)
	{
		x = 0;
		while (x < bmp->width)
		{
			img[y * bmp->width + x] = *(unsigned int*)(data->img->address +
					((bmp->height - y) * data->img->line_size + x *
									(data->img->bits_per_pixel / 8)));
			x++;
		}
		y++;
	}
	write(fd, img, bmp->sizeimage);
	free(img);
}
