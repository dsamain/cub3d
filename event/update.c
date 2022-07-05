/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:42:28 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/03 17:27:00 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update(t_data *data, t_player *player)
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
