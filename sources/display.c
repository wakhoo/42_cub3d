/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:22:11 by dancel            #+#    #+#             */
/*   Updated: 2025/03/21 16:22:53 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_big_pixel(t_doint p, int color, int size, t_data *data)
{
	t_doint	q;
	double	dy;
	double	dx;
	double	delta;

	dy = -1;
	while (++dy < size)
	{
		dx = -1;
		while (++dx < size)
		{
			q.x = p.x * (SCALE + 4) + dx;
			q.y = p.y * (SCALE + 4) + dy;
			delta = pow(q.x - (RADIUS * (SCALE + 4)), 2) \
				+ pow(q.y - (RADIUS * (SCALE + 4)), 2);
			if (delta < pow(RADIUS * (SCALE + 4), 2))
				draw_pixel(data->screen, q.x, q.y, color);
		}
	}
}

static t_doint	relative_coord(t_doint p, t_data *data)
{
	p.x = p.x - data->player.x + RADIUS;
	p.y = p.y - data->player.y + RADIUS;
	return (p);
}

static void	draw_elements(t_doint p, t_data *data)
{
	if (ft_is_in_the_set(data->map[(int)p.y][(int)p.x], "1"))
		draw_big_pixel(relative_coord(p, data), 0x00FF00FF, SCALE, data);
	if (ft_is_in_the_set(data->map[(int)p.y][(int)p.x], "2"))
		draw_big_pixel(relative_coord(p, data), 0x008F00FF, SCALE, data);
	if (ft_is_in_the_set(data->map[(int)p.y][(int)p.x], "3"))
		draw_big_pixel(relative_coord(p, data), 0x008F8FFF, SCALE, data);
	if (ft_is_in_the_set(data->map[(int)p.y][(int)p.x], "0NWES"))
		draw_big_pixel(relative_coord(p, data), 0x00000000, SCALE, data);
}

static void	draw_minimap(t_data *data)
{
	t_doint	p;

	p.y = data->player.y - RADIUS;
	while (p.y <= data->player.y + RADIUS)
	{
		p.x = data->player.x - RADIUS;
		while (p.x <= data->player.x + RADIUS)
		{
			p.y = floor(p.y);
			p.x = floor(p.x);
			if (p.y >= 0 && p.y < ft_tab_size(data->map) && p.x >= 0
				&& p.x < (int)ft_strlen(data->map[(int)p.y]))
				draw_elements(p, data);
			p.x++;
		}
		p.y++;
	}
	draw_big_pixel((t_doint){RADIUS - 0.5, RADIUS - 0.5}, \
		0xFF0000FF, 20, data);
	draw_big_pixel((t_doint){RADIUS - 0.5 + data->player.dx * RADIUS, \
		RADIUS - 0.5 + data->player.dy * RADIUS}, 0xFF0000FF, 20, data);
}

void	display(t_data *data)
{
	data->y_start += 2;
	if (data->y_start >= (int)data->wall.i_e.img_ptr->height)
		data->y_start = 0;
	render_frame(data);
	if (data->bonus)
		draw_minimap(data);
	mlx_image_to_window(data->mlx, data->screen, 0, 0);
}
