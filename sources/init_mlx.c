/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:21:19 by dancel            #+#    #+#             */
/*   Updated: 2025/03/21 16:26:14 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(int x, int y, int c, t_data *data)
{
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (ft_strchr("NWSE", data->map[y][x]))
			{
				data->player.x = x;
				data->player.y = y;
				data->player.sx = x * TILE;
				data->player.sy = y * TILE;
				c = data->map[y][x];
				data->player.dx = (c == 'E') - (c == 'W');
				data->player.dy = (c == 'S') - (c == 'N');
				data->player.px = tan((FOV / 2) * (M_PI / 180.0)) \
				* ((c == 'N') - (c == 'S'));
				data->player.py = tan((FOV / 2) * (M_PI / 180.0)) \
				* ((c == 'E') - (c == 'W'));
				return ;
			}
		}
	}
}

static void	run(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->is_running == 1)
		pos_change(data, data->player.dx, data->player.dy, 1);
}

t_image	new_image(char *path, int flag, t_data *data)
{
	t_image	img;

	img.png_ptr = mlx_load_png(path);
	if (!img.png_ptr)
		exit_cub3d("Error :\nimage not found", data);
	img.img_ptr = mlx_texture_to_image(data->mlx, img.png_ptr);
	if (!img.img_ptr)
		exit_cub3d("Error :\nimage not found\n", data);
	img.width = img.png_ptr->width;
	img.height = img.png_ptr->height;
	if (flag == 1 && (img.width != data->wall.i_n.width \
		|| img.height != data->wall.i_n.height))
		exit_cub3d("Error :\ntextures have different dimensions\n", data);
	return (img);
}

void	init_mlx(t_data *data)
{
	init_player(-1, -1, -1, data);
	data->screen = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->screen)
		exit_cub3d("Error:\nFailed to create screen image\n", data);
	data->x_mouse = 0;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	data->title = new_image(TITLE, 0, data);
	mlx_image_to_window(data->mlx, data->title.img_ptr, \
		(WIDTH - data->title.img_ptr->width) / 2, 0);
	if (data->bonus)
	{
		mlx_cursor_hook(data->mlx, cursor_hook, data);
		mlx_mouse_hook(data->mlx, mouse_hook, data);
	}
	mlx_loop_hook(data->mlx, run, data);
	mlx_close_hook(data->mlx, close_hook, data);
	mlx_loop_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
}
