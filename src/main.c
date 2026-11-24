/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 17:43:43 by mlejamte          #+#    #+#             */
/*   Updated: 2026/11/24 18:33:47 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void init_dir_to_0(t_data *d)
{
	d->dirX = 0;
	d->dirY = 0;
	d->planX = 0;
	d->planY = 0;
}

void	fill_background(t_data *d)
{
	int			i;
	mlx_color	ceil_c;
	mlx_color	floor_c;

	ceil_c.rgba = ((unsigned int)d->map->color_Ceiling << 8) | 0xFF;
	floor_c.rgba = ((unsigned int)d->map->color_Floor << 8) | 0xFF;
	i = 0;
	while (i < WIN_W * WIN_H / 2)
		d->buf[i++] = ceil_c;
	while (i < WIN_W * WIN_H)
		d->buf[i++] = floor_c;
}

void	init_dir(t_data *d)
{
	int	o;

	init_dir_to_0(d);
	o = d->map->orientation_player;
	if (o == 'N')
	{
		d->dirY = -1;
		d->planX = 0.66;
	}
	else if (o == 'S')
	{
		d->dirY = 1;
		d->planX = -0.66;
	}
	else if (o == 'E')
	{
		d->dirX = 1;
		d->planY = 0.66;
	}
	else if (o == 'W')
	{
		d->dirX = -1;
		d->planY = -0.66;
	}
}


void	print_screen(void *param)
{
	t_data	*d;
	t_ray	ray;
	int		x;

	d = (t_data *)param;
	mlx_clear_window(d->mlx, d->win, (mlx_color){.rgba = 0x000000FF});
	update_player(d);
	fill_background(d);
	x = 0;
		while (x < WIN_W)
	{
		init_ray(d, &ray, x);
		run_dda(d, &ray);
		compute_line(&ray);
		compute_tex(d, &ray);
		draw_column(d, &ray, x);
		x++;
	}
	mlx_set_image_region(d->mlx, d->screen, 0, 0, WIN_W, WIN_H, d->buf);
	mlx_put_image_to_window(d->mlx, d->win, d->screen, 0, 0);
}

void	init_data(t_data *d)
{
	mlx_window_create_info info;

	info = (mlx_window_create_info){NULL, "cub3D", 1920, 1080, 0, 0};
	d->mlx = mlx_init();
	if (d->mlx == NULL)
		exit(1);//a modifierrrrrr
	d->win = mlx_new_window(d->mlx, &info);
	if (d->win == NULL)
		exit(1);//a modifierrrrrr
	d->tex = ft_calloc(4, sizeof(t_tex));
	if (load_all_tex(d))
	{
		write(2, "Error\ntexture\n", 14);
		exit(1);
	}
	d->buf = malloc(sizeof(mlx_color) * WIN_W * WIN_H);
	if (d->buf == NULL)
		exit(1);
	d->screen = mlx_new_image(d->mlx, 1920, 1080);
	mlx_clear_window(d->mlx, d->win,(mlx_color){ .rgba = 0x000000FF });
	init_dir(d);
	d->keys = ft_calloc(512, sizeof(int));
	if (d->keys == NULL)
		exit(1);//a modifierrrrrr
	d->mouse_on = 0;
}

#include <stdlib.h>
#include <string.h>

void	init_cub3d(t_cub3dparsing *data)
{

	char	*map[] = {
		"1111111111111111111111111",
		"1000000000110000000000001",
		"1011000001110000000000001",
		"100100000000000000000000111111111",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"1N000000000000001101010010001",
		"1100000111010101111101111000111",
		"11110111101010110111101000111",
		"111111111111111111111111111",
		NULL
	};
	int	i;

	i = 0;
	data->file_NO = strdup("texture/pierre.jpg");
	data->file_SO = strdup("texture/Spritz.jpg");
	data->file_WE = strdup("texture/caca.jpg");
	data->file_EA = strdup("texture/wall.jpg");
	data->color_Floor = 100 << 16 | 100 << 8 | 100;
	data->color_Ceiling = 50 << 16 | 50 << 8 | 100;
	data->map_height = 14;
	data->map_width = 0;
	while (map[i])
	{
		if ((int)strlen(map[i]) > data->map_width)
			data->map_width = strlen(map[i]);
		i++;
	}
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	i = 0;
	while (map[i])
	{
		data->map[i] = strdup(map[i]);
		i++;
	}
	data->map[i] = NULL;
	data->pos_column = 1.5;
	data->pos_row = 10.5;
	data->orientation_player = 'N';
}

int main ()
{
	t_data *d;
	int		i;
	d = malloc(sizeof(t_data));
	d->map = malloc(sizeof(t_cub3dparsing));
	init_cub3d(d->map);

	init_data(d);
	mlx_add_loop_hook(d->mlx, &print_screen, (void *)d );
	mlx_on_event(d->mlx, d->win, MLX_KEYDOWN, key_down, d);
	mlx_on_event(d->mlx, d->win, MLX_KEYUP, key_up, d);
	mlx_on_event(d->mlx, d->win, MLX_WINDOW_EVENT, window_hook, d->mlx);
	mlx_loop(d->mlx);
	mlx_destroy_image(d->mlx,d->screen);
	mlx_destroy_window(d->mlx, d->win);
	mlx_destroy_context(d->mlx);
	free(d->buf);
	free(d->keys);
	i = 0;
	while (i < 4)
		free(d->tex[i++].px);
	free(d->tex);
	free(d);
}
