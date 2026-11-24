/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 17:14:49 by mlejamte          #+#    #+#             */
/*   Updated: 2026/11/24 17:58:16 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	load_tex(t_data *d, t_tex *t, char *path)
{
	mlx_image	img;
	int			i;

	img = mlx_new_image_from_file(d->mlx, path, &t->w, &t->h);
	if (img == NULL)
		return (1);
	t->px = malloc(sizeof(mlx_color) * t->w * t->h);
	if (t->px == NULL)
	{
		mlx_destroy_image(d->mlx, img);
		return (1);
	}
	i = 0;
	while (i < t->w * t->h)
	{
		t->px[i] = mlx_get_image_pixel(d->mlx, img, i % t->w, i / t->w);
		i++;
	}
	mlx_destroy_image(d->mlx, img);
	return (0);
}

int	load_all_tex(t_data *d)
{
	t_cub3dparsing	*m;

	m = d->map;
	if (load_tex(d, &d->tex[0], m->file_NO)
		|| load_tex(d, &d->tex[1], m->file_SO)
		|| load_tex(d, &d->tex[2], m->file_WE)
		|| load_tex(d, &d->tex[3], m->file_EA))
		return (1);
	return (0);
}

void	compute_line(t_ray *r)
{
	if (r->perp < 0.01)
		r->perp = 0.01;
	r->line_h = (int)(WIN_H / r->perp);
	r->start = WIN_H / 2 - r->line_h / 2;
	r->end = WIN_H / 2 + r->line_h / 2;
	if (r->end >= WIN_H)
		r->end = WIN_H - 1;
}

void	compute_tex(t_data *d, t_ray *r)
{
	t_tex	*t;

	if (r->side == 0)
		r->wallX = d->map->pos_row + r->perp * r->rayY;
	else
		r->wallX = d->map->pos_column + r->perp * r->rayX;
	r->wallX -= floor(r->wallX);
	if (r->side == 0 && r->rayX > 0)
		r->tex_id = 3;
	else if (r->side == 0)
		r->tex_id = 2;
	else if (r->rayY > 0)
		r->tex_id = 1;
	else
		r->tex_id = 0;
	t = &d->tex[r->tex_id];
	r->texX = (int)(r->wallX * t->w);
	if ((r->side == 0 && r->rayX > 0) || (r->side == 1 && r->rayY < 0))
		r->texX = t->w - r->texX - 1;
	if (r->texX < 0)
		r->texX = 0;
	if (r->texX >= t->w)
		r->texX = t->w - 1;
}

