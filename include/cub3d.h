/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:20:35 by dancel            #+#    #+#             */
/*   Updated: 2025/03/21 16:29:11 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <math.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>

# define TITLE	"images/title.png"
# define W_N	"images/w_n.png"
# define W_W	"images/w_w.png"
# define W_S	"images/w_s.png"
# define W_E	"images/w_e.png"
# define DOOR	"images/door.png"

# define WIDTH			1600
# define HEIGHT		 	1200
# define TILE			30
# define SCALE			20
# define RADIUS			5.5
# define FOV			66
# define SPEED			0.3
# define ROT_SPEED		0.1

typedef struct s_point
{
	int	x;
	int	y;
}			t_point;

typedef struct s_doint
{
	double	x;
	double	y;
}			t_doint;

typedef struct s_image
{
	mlx_image_t		*img_ptr;
	mlx_texture_t	*png_ptr;
	int				width;
	int				height;
}	t_image;

typedef struct s_pixel
{
	int			r;
	int			g;
	int			b;
	int			a;
	uint32_t	color;
}	t_pixel;

typedef struct s_wall
{
	t_image		i_n;
	t_image		i_w;
	t_image		i_s;
	t_image		i_e;
	t_image		door;
}	t_wall;

typedef struct s_player
{
	double	x;
	double	y;
	double	sx;
	double	sy;
	double	dx;
	double	dy;
	double	px;
	double	py;
}	t_player;

typedef struct s_data
{
	int			bonus;
	char		**file;
	char		**map;
	mlx_t		*mlx;
	mlx_image_t	*screen;
	t_image		title;
	double		x_mouse;
	int			is_running;
	int			frame;
	int			start;
	int			y_start;
	t_player	player;
	t_wall		wall;
	t_pixel		floor;
	t_pixel		ceiling;
	int			fd;
}			t_data;

typedef struct s_ray
{
	t_doint	cam;
	t_doint	ray;
	t_point	map;
	t_point	step;
	t_doint	delta;
	t_doint	sidedis;
	int		hit;
	int		side;
	double	perpwalldist;
}	t_ray;

typedef struct s_draw_wall
{
	int			lineh;
	int			startd;
	int			endd;
	t_image		*select;
	uint8_t		*pixel;
	uint32_t	color;
	double		wallx;
	t_point		pselec;
}	t_draw_wall;

/*

# main.c
# ============================*/
void		exit_cub3d(char *error, t_data *data);
void		update_minimap(void *param);
void		close_hook(void *param);
int32_t		main(int ac, char **av);
/*

# parsing.c
# ============================*/
char		*find_value(char *s, t_data *data);
int			get_pixel(char *s, t_pixel *pixel);
void		find_the_map(t_data *data);
void		check_the_map(t_data *data);
void		parse_the_file(t_data *data);
/*

# utils_bonus.c
# ============================*/
void		action_key(t_data *data);
void		bonus_redirection(t_data *data);
/*

# init_mlx.c
# ============================*/
void		init_mlx(t_data *data);
t_image		new_image(char *path, int flag, t_data *data);
/*

# display.c
# ============================*/
void		display(t_data *data);
/*

# hooker.c
# ============================*/
void		pos_change(t_data *data, double valueX, double valueY, int dir);
void		cursor_hook(double x, double y, void *param);
void		mouse_hook(enum mouse_key button, enum action action \
				, enum modifier_key mods, void *param);
void		key_hook(void *param);
/*

# ray_cast.c
# ============================*/
void		render_frame(t_data *data);
/*

# ray_utils.c
# ============================*/
int			set_pselc(t_data *data, t_draw_wall draw, int y);
t_image		*select_texture(t_data *data, t_ray ray, int wd);
void		init_ray(t_data *data, t_ray *ray, int x);
void		init_draw(t_data *data, t_ray ray, t_draw_wall *draw, int wd);
/*

# utils.c
# ============================*/
void		destroy_image(t_image img, t_data *data);
void		draw_pixel(mlx_image_t *image, int x, int y, uint32_t color);
uint32_t	create_rgb(int r, int g, int b, int a);

#endif