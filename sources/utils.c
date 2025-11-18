/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:43:40 by dancel            #+#    #+#             */
/*   Updated: 2025/03/21 14:52:06 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	create_rgb(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	destroy_image(t_image img, t_data *data)
{
	if (img.img_ptr)
	{
		mlx_delete_image(data->mlx, img.img_ptr);
		img.img_ptr = NULL;
		mlx_delete_texture(img.png_ptr);
		img.png_ptr = NULL;
	}
}

void	draw_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	int	index;

	if (!image || x < 0 || x >= (int)image->width
		|| y < 0 || y >= (int)image->height || color % 100 == 0)
		return ;
	index = (y * image->width + x) * 4;
	image->pixels[index + 0] = (color >> 24) & 0xFF;
	image->pixels[index + 1] = (color >> 16) & 0xFF;
	image->pixels[index + 2] = (color >> 8) & 0xFF;
	image->pixels[index + 3] = (color) & 0xFF;
}
