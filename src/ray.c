/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 16:31:09 by mlejamte          #+#    #+#             */
/*   Updated: 2026/11/24 18:00:08 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_delta_step(t_data *d, t_ray *r)
{
	if (r->rayX == 0)
		r->deltaX = 1e30;
	else
		r->deltaX = fabs(1 / r->rayX)
	if (r->rayY == 0)
		r->deltaY = 1e30;
	else
		r->deltaY = fabs(1 / r->rayY)
	if (r->rayX < 0)
		r->stepX = -1;
	else
		r->stepX = 1;
	if (r->rayY < 0)
		r->stepY = -1;
	else
		r->stepY = 1;
}

void	init_ray(t_data *d, t_ray *r, int x)
{
	double	cam;

	cam = 2.0 * x / WIN_W - 1;
	r->rayX = d->dirX + d->planX * cam;
	r->rayY = d->dirY + d->planY * cam;
	r->mapX = (int)d->map->pos_column;
	r->mapY = (int)d->map->pos_row;
	init_delta_step(d, r);
	if (r->rayX < 0)
		r->sideX = (d->map->pos_column - r->mapX) * r->deltaX;
	else
		r->sideX = (r->mapX + 1.0 - d->map->pos_column) * r->deltaX;
	if (r->rayY < 0)
		r->sideY = (d->map->pos_row - r->mapY) * r->deltaY;
	else
		r->sideY = (r->mapY + 1.0 - d->map->pos_row) * r->deltaY;
}

int	is_wall(t_data *d, int mx, int my)
{
	if (my < 0 || my >= d->map->map_height)
		return (1);
	if (mx < 0 || mx >= (int)ft_strlen(d->map->map[my]))
		return (1);
	if (d->map->map[my][mx] == '1')
		return (1);
	return (0);
}

void	run_dda(t_data *d, t_ray *r)
{
	while (1)
	{
		if (r->sideX < r->sideY)
		{
			r->sideX += r->deltaX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideY += r->deltaY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (is_wall(d, r->mapX, r->mapY))
			break ;
	}
	if (r->side == 0)
		r->perp = r->sideX - r->deltaX;
	else
		r->perp = r->sideY - r->deltaY;
}

void	draw_column(t_data *d, t_ray *r, int x)
{
	t_tex	*t;
	double	step;
	double	tex_pos;
	int		y;
	int		ty;

	t = &d->tex[r->tex_id];
	step = (double)t->h / r->line_h;
	y = r->start;
	if (y < 0)
		y = 0;
	tex_pos = (y - r->start) * step;
	while (y <= r->end)
	{
		ty = (int)tex_pos;
		if (ty >= t->h)
			ty = t->h - 1;
		d->buf[y * WIN_W + x] = t->px[ty * t->w + r->texX];
		tex_pos += step;
		y++;
	}
}
