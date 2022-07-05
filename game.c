/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:13:46 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/04 10:34:06 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_destroy(void *void_data)
{
	t_data	*data;

	data = void_data;
	g_clear(data, &data->garbage, "");
	exit(0);
	return (0);
}

void	game_loop(t_data *data)
{
	mlx_hook(data->win, 2, 1 << 0, key_press, data);
	mlx_hook(data->win, 3, 1 << 1, key_release, data);
	mlx_hook(data->win, 17, 0, on_destroy, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_loop_hook(data->mlx, game, data);
	mlx_loop(data->mlx);
}

int	game(void *void_data)
{
	t_data	*data;

	data = (t_data *)void_data;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pix, &data->line_length, &data->endian);
	update(data, &data->player);
	if (!data->free_mouse)
		mlx_mouse_hide();
	else
		mlx_mouse_show();
	move_player(data, &data->player);
	rotate_player(data, &data->player);
	render_floor_ceil(data);
	render_view(data);
	render_gun(data);
	if (data->toogle_minimap)
		minimap(data, &data->mini_map);
	return (1);
}
