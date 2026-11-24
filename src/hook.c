/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 16:03:11 by mlejamte          #+#    #+#             */
/*   Updated: 2026/11/18 16:03:11 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	key_down(int key, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (key == KEY_ESC)
		mlx_loop_end(d->mlx);
	if (key == KEY_TAB)
	{
		d->mouse_on = !d->mouse_on;
		if (d->mouse_on)
		{
			mlx_mouse_hide(d->mlx);
			mlx_mouse_move(d->mlx, d->win, WIN_W / 2, WIN_H / 2);
		}
		else
			mlx_mouse_show(d->mlx);
	}
	if (key >= 0 && key < 512)
		d->keys[key] = 1;
}

void	key_up(int key, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (key >= 0 && key < 512)
		d->keys[key] = 0;
}

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end((mlx_context)param);
}


