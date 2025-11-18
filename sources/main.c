/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:27:12 by dancel            #+#    #+#             */
/*   Updated: 2025/03/21 16:27:14 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_cub3d(char *error, t_data *data)
{
	write(2, error, ft_strlen(error));
	if (data)
	{
		ft_free_tab(data->file);
		destroy_image(data->wall.i_n, data);
		destroy_image(data->wall.i_w, data);
		destroy_image(data->wall.i_s, data);
		destroy_image(data->wall.i_e, data);
		if (data->mlx)
			mlx_terminate(data->mlx);
		if (data->fd > 0)
			close(data->fd);
		free(data);
	}
	exit(error[0] != '\0');
}

void	close_hook(void *param)
{
	exit_cub3d("", param);
}

static void	read_the_file(char **av, t_data *data)
{
	char	*s1;
	char	*s2;
	char	*s3;

	data->fd = open(av[1], O_RDONLY);
	if (data->fd == -1)
		exit_cub3d("Error :\nmap unfind", data);
	s1 = get_next_line(data->fd);
	if (!s1)
		exit_cub3d("Error :\nmap unreadable", data);
	while (1)
	{
		s2 = get_next_line(data->fd);
		if (!s2)
			break ;
		s3 = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
		if (!s3)
			exit_cub3d("Error :\nmalloc failed", data);
		s1 = s3;
	}
	data->file = ft_split(s1, '\n');
	free(s1);
}

int32_t	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_cub3d("Error :\nmalloc failed", data);
	*data = (t_data){0};
	if (ac != 2)
		exit_cub3d("Error :\nusage : <map.cub>", data);
	if (!ft_strsuffix(av[1], ".cub"))
		exit_cub3d("Error :\nwrong extension", data);
	read_the_file(av, data);
	parse_the_file(data);
	init_mlx(data);
	exit_cub3d("", data);
}
