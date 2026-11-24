/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 17:27:26 by mlejamte          #+#    #+#             */
/*   Updated: 2026/11/24 16:25:32 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	rotate(t_data *d, double a)
{
	double	old_dir;
	double	old_plan;

	old_dir = d->dirX;
	old_plan = d->planX;
	d->dirX = d->dirX * cos(a) - d->dirY * sin(a);
	d->dirY = old_dir * sin(a) + d->dirY * cos(a);
	d->planX = d->planX * cos(a) - d->planY * sin(a);
	d->planY = old_plan * sin(a) + d->planY * cos(a);
}

void	update_mouse(t_data *d)
{
	int	mx;
	int	my;

	if (!d->mouse_on)
		return ;
	mlx_mouse_get_pos(d->mlx, &mx, &my);
	rotate(d, (mx - WIN_W / 2) * MOUSE_SENS);
	mlx_mouse_move(d->mlx, d->win, WIN_W / 2, WIN_H / 2);
}

void	try_move(t_data *d, double dx, double dy)
{
	double	m;

	m = MARGIN;
	if (dx < 0)
		m = -MARGIN;
	if (!is_wall(d, (int)(d->map->pos_column + dx + m),
		(int)d->map->pos_row))
		d->map->pos_column += dx;

	m = MARGIN;
	if (dy < 0)
		m = -MARGIN;
	if (!is_wall(d, (int)d->map->pos_column,
		(int)(d->map->pos_row + dy + m)))
		d->map->pos_row += dy;
}

void	update_player(t_data *d)
{
	update_mouse(d);
	if (d->keys[KEY_W])
		try_move(d, d->dirX * MOVE_SPEED, d->dirY * MOVE_SPEED);
	if (d->keys[KEY_S])
		try_move(d, -d->dirX * MOVE_SPEED, -d->dirY * MOVE_SPEED);
	if (d->keys[KEY_D])
		try_move(d, -d->dirY * MOVE_SPEED, d->dirX * MOVE_SPEED);
	if (d->keys[KEY_A])
		try_move(d, d->dirY * MOVE_SPEED, -d->dirX * MOVE_SPEED);
	if (d->keys[KEY_RIGHT])
		rotate(d, ROT_SPEED);
	if (d->keys[KEY_LEFT])
		rotate(d, -ROT_SPEED);
}
