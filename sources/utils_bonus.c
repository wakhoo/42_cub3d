/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:29:01 by dancel            #+#    #+#             */
/*   Updated: 2025/03/21 16:29:03 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	action_door(int dir, t_data *data)
{
	if (dir == 1 && data->player.dx > -0.5
		&& data->player.dx < 0.5 && data->player.dy < 0)
		data->map[(int)(data->player.y) - 1][(int)(data->player.x)] = '5' - \
		(data->map[(int)(data->player.y) - 1][(int)(data->player.x)] - '0');
	if (dir == 2 && data->player.dx > -0.5
		&& data->player.dx < 0.5 && data->player.dy > 0)
		data->map[(int)(data->player.y) + 1][(int)(data->player.x)] = '5' - \
		(data->map[(int)(data->player.y) + 1][(int)(data->player.x)] - '0');
	if (dir == 3 && data->player.dy > -0.5
		&& data->player.dy < 0.5 && data->player.dx < 0)
		data->map[(int)(data->player.y)][(int)(data->player.x) - 1] = '5' - \
		(data->map[(int)(data->player.y)][(int)(data->player.x) - 1] - '0');
	if (dir == 4 && data->player.dy > -0.5
		&& data->player.dy < 0.5 && data->player.dx > 0)
		data->map[(int)(data->player.y)][(int)(data->player.x) + 1] = '5' - \
		(data->map[(int)(data->player.y)][(int)(data->player.x) + 1] - '0');
}

void	action_key(t_data *data)
{
	if (data->start == 0)
	{
		if (data->title.img_ptr != NULL && data->start == 0)
			destroy_image(data->title, data);
		data->start = 1;
	}
	if (ft_is_in_the_set(\
		data->map[(int)(data->player.y) - 1][(int)(data->player.x)], "23"))
		action_door(1, data);
	if (ft_is_in_the_set(\
		data->map[(int)(data->player.y) + 1][(int)(data->player.x)], "23"))
		action_door(2, data);
	if (ft_is_in_the_set(\
		data->map[(int)(data->player.y)][(int)(data->player.x) - 1], "23"))
		action_door(3, data);
	if (ft_is_in_the_set(\
		data->map[(int)(data->player.y)][(int)(data->player.x) + 1], "23"))
		action_door(4, data);
}

static void	check_the_map_bonus(t_data *data)
{
	int	i;
	int	j;
	int	spawn;

	i = -1;
	spawn = 0;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (!ft_is_in_the_set(data->map[i][j], "0123NWES \0"))
				exit_cub3d("Error\nunknown element in the map\n", data);
			if (ft_is_in_the_set(data->map[i][j], "NWES"))
				spawn++;
			if (ft_is_in_the_set(data->map[i][j], "023NWES")
				&& (!ft_is_in_the_set(data->map[i - 1][j], "1023NWES")
				|| !ft_is_in_the_set(data->map[i + 1][j], "1023NWES")
				|| !ft_is_in_the_set(data->map[i][j - 1], "1023NWES")
				|| !ft_is_in_the_set(data->map[i][j + 1], "1023NWES")))
				exit_cub3d("Error\nmap is not enclosed\n", data);
		}
	}
	if (spawn != 1)
		exit_cub3d("Error\ninvalid spawn\n", data);
}

void	bonus_redirection(t_data *data)
{
	if (!data->bonus)
	{
		find_the_map(data);
		check_the_map(data);
	}
	else if (data->bonus)
	{
		if (find_value("DO ", data))
			data->wall.door = new_image(find_value("DO ", data), 1, data);
		else
			data->wall.door = new_image(DOOR, 1, data);
		find_the_map(data);
		check_the_map_bonus(data);
	}
}
