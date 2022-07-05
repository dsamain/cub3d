/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:40:24 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/04 10:36:38 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./mlx/mlx.h"

void	free_all(t_data *data)
{
	int	i;

	if (!data->mlx)
		return ;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mini_map.img)
		mlx_destroy_image(data->mlx, data->mini_map.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	i = -1;
	while (++i < SPRITE_SIZE)
		if (data->sprite[i].img)
			mlx_destroy_image(data->mlx, data->sprite[i].img);
	i = -1;
	while (++i < 4)
		if (data->texture[i].img)
			mlx_destroy_image(data->mlx, data->texture[i].img);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		printf("invalid number of arg\n");
		return (0);
	}
	init_data(&data);
	if (!parse(&data, av[1]))
		return (0);
	init_player(&data, "12100121");
	init_image_null(&data);
	init_mlx(&data);
	init_textures(&data);
	init_map(&data);
	init_sprite(&data);
	game_loop(&data);
}
