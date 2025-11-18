/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:57:44 by dancel            #+#    #+#             */
/*   Updated: 2025/03/20 18:26:40 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*find_value(char *s, t_data *data)
{
	int		i;
	int		j;
	char	*value;

	i = -1;
	value = NULL;
	while (data->file[++i])
	{
		j = 0;
		value = ft_strstr(data->file[i], s);
		if (value)
		{
			value = value + ft_strlen(s);
			while (ft_iswhitespace(value[j]))
				j++;
			break ;
		}
	}
	return (value + j);
}

int	get_pixel(char *s, t_pixel *pixel)
{
	int		i;

	i = 0;
	if (ft_strchrcounter(s, ',') != 2 || ft_strstr(s, ",,"))
		return (write(2, "Error :\ninvalid color has been changed\n", 40));
	while (ft_iswhitespace(s[i]))
		i++;
	while (s[++i - 1])
	{
		if (!(ft_isdigit(s[i]) || s[i] == ',' || s[i] == '\0'))
			return (write(2, "Error :\ninvalid color has been changed\n", 40));
	}
	pixel->r = ft_atoi(s);
	pixel->g = ft_atoi(ft_strchr(s, ',') + 1);
	pixel->b = ft_atoi(ft_strchr((ft_strchr(s, ',') + 1), ',') + 1);
	if (pixel->r > 255 || pixel->g > 255 || pixel->b > 255 || pixel->r < 0)
	{
		*pixel = (t_pixel){0};
		return (write(2, "Error :\ninvalid color has been changed\n", 40));
	}
	pixel->color = create_rgb(pixel->r, pixel->g, pixel->b, 255);
	return (0);
}

void	find_the_map(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (data->file[i][++j])
	{
		if (!(ft_is_in_the_set(data->file[i][j], "1 ")))
		{
			i++;
			j = -1;
		}
		else if (!data->file[i][j + 1])
		{
			data->map = data->file + i;
			return ;
		}
	}
	exit_cub3d("Error ;\nmap unfound\n", data);
}

void	check_the_map(t_data *data)
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
			if (!ft_is_in_the_set(data->map[i][j], "01NWES \0"))
				exit_cub3d("Error\nunknown element in the map\n", data);
			if (ft_is_in_the_set(data->map[i][j], "NWES"))
				spawn++;
			if (ft_is_in_the_set(data->map[i][j], "0NWES")
				&& (!ft_is_in_the_set(data->map[i - 1][j], "10NWES")
				|| !ft_is_in_the_set(data->map[i + 1][j], "10NWES")
				|| !ft_is_in_the_set(data->map[i][j - 1], "10NWES")
				|| !ft_is_in_the_set(data->map[i][j + 1], "10NWES")))
				exit_cub3d("Error\nmap is not enclosed\n", data);
		}
	}
	if (spawn != 1)
		exit_cub3d("Error\ninvalid spawn\n", data);
}

void	parse_the_file(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D : ENTER THE MATRIX", true);
	if (!data->mlx)
		exit_cub3d("Error :\nmlx pointer not found\n", data);
	if (find_value("NO ", data))
		data->wall.i_n = new_image(find_value("NO ", data), 0, data);
	else
		data->wall.i_n = new_image(W_N, 0, data);
	if (find_value("WE ", data))
		data->wall.i_w = new_image(find_value("WE ", data), 1, data);
	else
		data->wall.i_w = new_image(W_W, 1, data);
	if (find_value("SO ", data))
		data->wall.i_s = new_image(find_value("SO ", data), 1, data);
	else
		data->wall.i_s = new_image(W_S, 1, data);
	if (find_value("EA ", data))
		data->wall.i_e = new_image(find_value("EA ", data), 1, data);
	else
		data->wall.i_e = new_image(W_E, 0, data);
	if (find_value("F ", data))
		get_pixel(find_value("F ", data), &data->floor);
	if (find_value("C ", data))
		get_pixel(find_value("C ", data), &data->ceiling);
	bonus_redirection(data);
}
