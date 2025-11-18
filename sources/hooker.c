/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:27:02 by dancel            #+#    #+#             */
/*   Updated: 2025/03/21 16:27:05 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotation(t_data *data, double dir)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->player.dx;
	oldplanex = data->player.px;
	data->player.dx = data->player.dx * cos(dir) - data->player.dy * sin(dir);
	data->player.dy = olddirx * sin(dir) + data->player.dy * cos(dir);
	data->player.px = data->player.px * cos(dir) - data->player.py * sin(dir);
	data->player.py = oldplanex * sin(dir) + data->player.py * cos(dir);
}

void	pos_change(t_data *data, double valueX, double valueY, int dir)
{
	double	x;
	double	y;
	double	player_size;

	x = data->player.x + dir * valueX * SPEED;
	y = data->player.y + dir * valueY * SPEED;
	player_size = 0.1;
	if (ft_is_in_the_set(\
		data->map[(int)(y - player_size)][(int)(x - player_size)], "12")
	|| ft_is_in_the_set(\
		data->map[(int)(y + player_size)][(int)(x - player_size)], "12")
	|| ft_is_in_the_set(\
		data->map[(int)(y - player_size)][(int)(x + player_size)], "12")
	|| ft_is_in_the_set(\
		data->map[(int)(y + player_size)][(int)(x + player_size)], "12"))
		return ;
	data->player.x = x;
	data->player.y = y;
}

void	cursor_hook(double x, double y, void *param)
{
	t_data	*data;

	(void)y;
	data = (t_data *)param;
	if (x < data->x_mouse)
		rotation(data, -ROT_SPEED / 3);
	else if (x > data->x_mouse)
		rotation(data, ROT_SPEED / 3);
	data->x_mouse = x;
	if (x < 50 || x > WIDTH - 50)
		mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
}

void	mouse_hook(enum mouse_key button, enum action action, \
					enum modifier_key mods, void *param)
{
	t_data	*data;

	(void)mods;
	data = (t_data *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
		{
			if (!data->start)
			{
				if (data->title.img_ptr != NULL && data->start == 0)
					destroy_image(data->title, data);
				data->start = 1;
			}
			data->is_running = 1;
		}
		else if (action == MLX_RELEASE)
			data->is_running = 0;
	}
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		action_key(data);
}

void	key_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER))
		action_key(data);
	if (data->start == 0)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit_cub3d("", data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) || \
	mlx_is_key_down(data->mlx, MLX_KEY_UP))
		pos_change(data, data->player.dx, data->player.dy, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || \
	mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		pos_change(data, data->player.dx, data->player.dy, -1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		pos_change(data, data->player.px, data->player.py, -1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		pos_change(data, data->player.px, data->player.py, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotation(data, -ROT_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotation(data, ROT_SPEED);
	display(data);
}
