/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:39:26 by dancel            #+#    #+#             */
/*   Updated: 2025/03/21 16:30:48 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_slice(t_data *data, int x, t_ray ray, int wd)
{
	t_draw_wall	draw;
	int			y;

	init_draw(data, ray, &draw, wd);
	if (ray.side == 0)
		draw.wallx = data->player.y + ray.perpwalldist * ray.ray.y;
	else
		draw.wallx = data->player.x + ray.perpwalldist * ray.ray.x;
	draw.wallx -= floor(draw.wallx);
	draw.pselec.x = (int)(draw.wallx * (double)draw.select->width);
	if ((ray.side == 0 && ray.ray.x > 0) || (ray.side == 1 && ray.ray.y < 0))
		draw.pselec.x = draw.select->width - draw.pselec.x - 1;
	y = draw.startd;
	while (y < draw.endd)
	{
		draw.pselec.y = set_pselc(data, draw, y);
		draw.pixel = &draw.select->img_ptr->pixels[(draw.pselec.y \
			* draw.select->width + draw.pselec.x) * 4];
		draw.color = create_rgb(\
			draw.pixel[0], draw.pixel[1], draw.pixel[2], draw.pixel[3]);
		draw_pixel(data->screen, x, y, draw.color);
		y++;
	}
}

static void	set_sidestep(t_data *data, t_ray *ray)
{
	if (ray->ray.x < 0)
	{
		ray->step.x = -1;
		ray->sidedis.x = (data->player.x - ray->map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedis.x = (ray->map.x + 1.0 - data->player.x) * ray->delta.x;
	}
	if (ray->ray.y < 0)
	{
		ray->step.y = -1;
		ray->sidedis.y = (data->player.y - ray->map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedis.y = (ray->map.y + 1.0 - data->player.y) * ray->delta.y;
	}
}

static void	dda(t_ray *ray, char c)
{
	if (c == 'x')
	{
		ray->sidedis.x += ray->delta.x;
		ray->map.x += ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->sidedis.y += ray->delta.y;
		ray->map.y += ray->step.y;
		ray->side = 1;
	}
}

static void	cast_ray(t_data *data, int x)
{
	t_ray	ray;

	init_ray(data, &ray, x);
	set_sidestep(data, &ray);
	while (ray.hit == 0)
	{
		if (ray.sidedis.x < ray.sidedis.y)
			dda(&ray, 'x');
		else
			dda(&ray, 'y');
		if (data->map[ray.map.y][ray.map.x] == '1' || \
			data->map[ray.map.y][ray.map.x] == '2')
			ray.hit = 1;
	}
	if (ray.side == 0)
		ray.perpwalldist = (ray.map.x - data->player.x \
			+ (1 - ray.step.x) / 2) / ray.ray.x;
	else
		ray.perpwalldist = (ray.map.y - data->player.y \
			+ (1 - ray.step.y) / 2) / ray.ray.y;
	if (ray.perpwalldist == 0)
		ray.perpwalldist = 0.0001;
	draw_wall_slice(data, x, ray, data->map[ray.map.y][ray.map.x] - '0');
}

void	render_frame(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	ft_memset(data->screen->pixels, 0, \
		data->screen->width * data->screen->height * 4);
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if (i < HEIGHT / 2)
				draw_pixel(data->screen, j, i, data->ceiling.color);
			else
				draw_pixel(data->screen, j, i, data->floor.color);
		}
	}
	j = -1;
	while (++j < WIDTH)
		cast_ray(data, j);
}
