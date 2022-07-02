/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 05:22:18 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/02 23:21:39 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player(t_data *data, t_player *player)
{
	if (player->move_up)
		player->vel_u = ft_fmin(player->vel_u + ACC, MAX_SPEED);
	else
		player->vel_u = ft_fmax(player->vel_u - ACC, 0);
	if (player->move_down)
		player->vel_d = ft_fmin(player->vel_d + ACC, MAX_SPEED);
	else
		player->vel_d = ft_fmax(player->vel_d - ACC, 0);
	if (player->move_left)
		player->vel_l = ft_fmin(player->vel_l + ACC, MAX_SPEED);
	else
		player->vel_l = ft_fmax(player->vel_l - ACC, 0);
	if (player->move_right)
		player->vel_r = ft_fmin(player->vel_r + ACC, MAX_SPEED);
	else
		player->vel_r = ft_fmax(player->vel_r - ACC, 0);
	data->sprite_cnt = ft_max(0, data->sprite_cnt - 1);
}

int	close_to_portal2(t_data *data, t_pos *pos)
{
	if (data->portal[1].ori == 2 && fabs(pos->x - (data->portal[1].pos.x + 0.5))
		< 0.2 && fabs(pos->y - data->portal[1].pos.y) <= 0.15)
		return (1);
	if (data->portal[1].ori == 0 && fabs(pos->x - (data->portal[1].pos.x + 0.5))
		< 0.2 && fabs(pos->y - (data->portal[1].pos.y + 1)) <= 0.15)
		return (1);
	if (data->portal[1].ori == 1 && fabs(pos->y - (data->portal[1].pos.y + 0.5))
		< 0.2 && fabs(pos->x - (data->portal[1].pos.x + 1)) <= 0.15)
		return (1);
	if (data->portal[1].ori == 3 && fabs(pos->y - (data->portal[1].pos.y + 0.5))
		< 0.2 && fabs(pos->x - (data->portal[1].pos.x)) <= 0.15)
		return (1);
	return (-1);
}

int	close_to_portal(t_data *data, t_pos *pos)
{
	if (data->portal[0].ori == -1 || data->portal[1].ori == -1)
		return (-1);
	if (data->portal[0].ori == 2 && fabs(pos->x - (data->portal[0].pos.x + 0.5))
		< 0.2 && fabs(pos->y - data->portal[0].pos.y) <= 0.15)
		return (0);
	if (data->portal[0].ori == 0 && fabs(pos->x - (data->portal[0].pos.x + 0.5))
		< 0.2 && fabs(pos->y - (data->portal[0].pos.y + 1)) <= 0.15)
		return (0);
	if (data->portal[0].ori == 1 && fabs(pos->y - (data->portal[0].pos.y + 0.5))
		< 0.2 && fabs(pos->x - (data->portal[0].pos.x + 1)) <= 0.15)
		return (0);
	if (data->portal[0].ori == 3 && fabs(pos->y - (data->portal[0].pos.y + 0.5))
		< 0.2 && fabs(pos->x - (data->portal[0].pos.x)) <= 0.15)
		return (0);
	return (close_to_portal2(data, pos));
}

int	teleporte2(t_data *data, t_player *player, int col, double gap)
{
	if (data->portal[!col].ori == 2)
	{
		player->pos.y = data->portal[!col].pos.y - 0.16;
		if (data->portal[col].ori == 0 || data->portal[col].ori == 3)
			player->pos.x = data->portal[!col].pos.x + gap;
		else
			player->pos.x = data->portal[!col].pos.x + 1 - gap;
	}
	if (data->portal[!col].ori == 1)
	{
		player->pos.x = data->portal[!col].pos.x + 1.16;
		if (data->portal[col].ori == 0 || data->portal[col].ori == 3)
			player->pos.y = data->portal[!col].pos.y + gap;
		else
			player->pos.y = data->portal[!col].pos.y + 1 - gap;
	}
	if (data->portal[!col].ori == 3)
	{
		player->pos.x = data->portal[!col].pos.x - 0.16;
		if (data->portal[col].ori == 2 || data->portal[col].ori == 1)
			player->pos.y = data->portal[!col].pos.y + gap;
		else
			player->pos.y = data->portal[!col].pos.y + 1 - gap;
	}
	return (1);
}

int	teleporte(t_data *data, t_player *player, t_pos *v, int col)
{
	double	gap;
	t_pos	pos;

	pos.x = player->pos.x + v->x;
	pos.y = player->pos.y + v->y;
	col = close_to_portal(data, &pos);
	if (col == -1)
		return (0);
	player->dir = get_new_ray_dir(data, &player->dir,
			data->portal[col].ori, data->portal[!col].ori + 2);
	if (data->portal[col].ori == 0 || data->portal[col].ori == 2)
		gap = fabs(data->portal[col].pos.x - pos.x);
	else
		gap = fabs(data->portal[col].pos.y - pos.y);
	if (data->portal[!col].ori == 0)
	{
		player->pos.y = data->portal[!col].pos.y + 1.16;
		if (data->portal[col].ori == 2 || data->portal[col].ori == 1)
			player->pos.x = data->portal[!col].pos.x + gap;
		else
			player->pos.x = data->portal[!col].pos.x + 1 - gap;
	}
	return (teleporte2(data, player, col, gap));
}
