/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:25:04 by dancel            #+#    #+#             */
/*   Updated: 2025/03/21 16:19:32 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_pselc(t_data *data, t_draw_wall draw, int y)
{
	int	bonus_y;

	if (data->bonus)
	{
		bonus_y = (((y - draw.startd) * draw.select->height) / \
		draw.lineh - data->y_start) % draw.select->height;
		if (bonus_y < 0)
			return (bonus_y + draw.select->height);
		else
			return (bonus_y);
	}
	else
		return (((y - draw.startd) * draw.select->height) / draw.lineh);
}

t_image	*select_texture(t_data *data, t_ray ray, int wd)
{
	if (wd == 2)
		return (&data->wall.door);
	else if (wd == 1 && ray.side == 0)
	{
		if (ray.step.x == 1)
			return (&data->wall.i_e);
		return (&data->wall.i_w);
	}
	else
	{
		if (wd == 1 && ray.step.y == 1)
			return (&data->wall.i_s);
		return (&data->wall.i_n);
	}
}

void	init_ray(t_data *data, t_ray *ray, int x)
{
	ray->cam.x = 2 * x / (double)WIDTH - 1;
	ray->ray.x = data->player.dx + data->player.px * ray->cam.x;
	ray->ray.y = data->player.dy + data->player.py * ray->cam.x;
	ray->map.x = (int)data->player.x;
	ray->map.y = (int)data->player.y;
	if (ray->ray.x == 0)
		ray->delta.x = fabs(1 / 0.0001);
	else
		ray->delta.x = fabs(1 / ray->ray.x);
	if (ray->ray.y == 0)
		ray->delta.y = fabs(1 / 0.0001);
	else
		ray->delta.y = fabs(1 / ray->ray.y);
	ray->hit = 0;
}

void	init_draw(t_data *data, t_ray ray, t_draw_wall *draw, int wd)
{
	draw->lineh = (int)(HEIGHT / ray.perpwalldist);
	draw->startd = -draw->lineh / 2 + HEIGHT / 2;
	if (draw->startd < 0)
		draw->startd = 0;
	draw->endd = draw->lineh / 2 + HEIGHT / 2;
	if (draw->endd >= HEIGHT)
		draw->endd = HEIGHT - 1;
	draw->select = select_texture(data, ray, wd);
}
