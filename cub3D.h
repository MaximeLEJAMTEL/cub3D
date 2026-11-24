/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 16:27:14 by mlejamte          #+#    #+#             */
/*   Updated: 2026/11/24 17:59:11 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <math.h>
#include "MacroLibX/includes/mlx.h"
#include "MacroLibX/includes/mlx_extended.h"
#include "src/libft/libft.h"

#define WIN_W 1920
#define WIN_H 1080
#define KEY_ESC 41
#define KEY_W 26
#define KEY_A 4
#define KEY_S 22
#define KEY_D 7
#define KEY_RIGHT 79
#define KEY_LEFT 80
#define MOVE_SPEED 0.03
#define ROT_SPEED 0.02
#define MARGIN 0.2
#define MOUSE_SENS 0.002
#define KEY_TAB 43

typedef struct s_ray
{
	double	rayX;
	double	rayY;
	double	deltaX;
	double	deltaY;
	double	sideX;
	double	sideY;
	double	perp;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		side;
	double	wallX;
	int		texX;
	int		tex_id;
	int		line_h;
	int		start;
	int		end;
}	t_ray;

typedef struct s_cub3dparsing
{
	char *file_NO;
	char *file_SO;
	char *file_WE;
	char *file_EA;
	int color_Floor;
	int color_Ceiling;
	char **map;
	int map_width;
	int map_height;
	double pos_column;
	double pos_row;
	int orientation_player;
}	t_cub3dparsing;

typedef struct s_tex
{
	mlx_color	*px;
	int			w;
	int			h;
}	t_tex;

typedef struct s_data
{
	t_cub3dparsing *map;
	mlx_context		mlx;
	mlx_window		win;
	mlx_image 		screen;
	double			dirX;
	double			dirY;
	double			planX;
	double			planY;
	int 			*keys;
	int				mouse_on;
	mlx_color		*buf;
	t_tex	*tex;
} t_data;



// hook.c
void	key_down(int key, void *param);
void	key_up(int key, void *param);
void	window_hook(int event, void *param);

// ray.h
void	init_ray(t_data *d, t_ray *r, int x);
int		is_wall(t_data *d, int mx, int my);
void	run_dda(t_data *d, t_ray *r);
void	draw_column(t_data *d, t_ray *r, int x);

// move.c
void	try_move(t_data *d, double dx, double dy);
void	update_player(t_data *d);

void	fill_background(t_data *d);
void print_screen(void *param);

// tex.c
int		load_all_tex(t_data *d);
void	compute_line(t_ray *r);
void	compute_tex(t_data *d, t_ray *r);
