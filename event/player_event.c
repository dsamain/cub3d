/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:39:00 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/04 10:27:03 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player(t_data *data, t_player *player)
{
	double	px;
	double	py;
	t_pos	v;
	int		div;

	px = player->pos.x;
	py = player->pos.y;
	div = 1 + (((player->move_down || player->move_up)
				+ (player->move_left || player->move_right) == 2)
			&& (player->move_down + player->move_up
				+ player->move_left + player->move_right == 2));
	v.y = SPEED * player->dir.y / div * player->vel_u
		- SPEED * player->dir.y / div * player->vel_d
		+ SPEED * player->dir.x / div * player->vel_l
		- SPEED * player->dir.x / div * player->vel_r;
	v.x = SPEED * player->dir.x / div * player->vel_u
		- SPEED * player->dir.x / div * player->vel_d
		+ SPEED * -player->dir.y / div * player->vel_l
		- SPEED * -player->dir.y / div * player->vel_r;
	if ((v.x || v.y) && teleporte(data, player, &v, 1))
		return ;
	collision(data, player, &v);
	player->pos.x += v.x;
	player->pos.y += v.y;
}

void	rotate_player(t_data *data, t_player *player)
{
	double	angle;
	double	tmpx;
	double	tmpy;
	int		x;
	int		y;

	if (!data->free_mouse)
	{
		mlx_mouse_get_pos(data->win, &x, &y);
		mlx_mouse_move(data->win, data->width / 2, data->height / 2 - 400);
		angle = (double)(data->width / 2 - x) / SENSITIVITY;
	}
	else
		angle = player->rotate_left * R_SPEED - player->rotate_right * R_SPEED;
	tmpx = data->player.dir.x;
	tmpy = data->player.dir.y;
	data->player.dir.x = cos(angle) * tmpx - sin(angle) * tmpy;
	data->player.dir.y = sin(angle) * tmpx + cos(angle) * tmpy;
	data->player.plane.x = data->player.dir.y * 0.66;
	data->player.plane.y = -data->player.dir.x * 0.66;
}
