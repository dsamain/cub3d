/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:05:01 by dsamain           #+#    #+#             */
/*   Updated: 2022/05/03 19:20:36 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keyCode, void *void_data)
{
	t_data	*data;

	data = void_data;
	if (keyCode == ESC)
	{
		g_clear(&data->garbage, "");
		free_all(data);
		exit(0);
	}
	data->player.move_up |= (keyCode == KEY_W);
	data->player.move_down |= (keyCode == KEY_S);
	data->player.move_left |= (keyCode == KEY_A);
	data->player.move_right |= (keyCode == KEY_D);
	data->player.rotate_left |= (keyCode == KEY_LEFT);
	data->player.rotate_right |= (keyCode == KEY_RIGHT);
	if (keyCode == KEY_O)
		set_portal(data, &data->player, 0);
	if (keyCode == KEY_P)
		set_portal(data, &data->player, 1);
	printf("key: %d pressed\n", keyCode);
	return (0);
}

int	key_release(int keyCode, void *void_data)
{
	t_data	*data;

	data = void_data;
	if (keyCode == KEY_W)
		data->player.move_up = 0;
	if (keyCode == KEY_S)
		data->player.move_down = 0;
	if (keyCode == KEY_A)
		data->player.move_left = 0;
	if (keyCode == KEY_D)
		data->player.move_right = 0;
	if (keyCode == KEY_LEFT)
		data->player.rotate_left = 0;
	if (keyCode == KEY_RIGHT)
		data->player.rotate_right = 0;
	printf("key %d released\n", keyCode);
	return (0);
}