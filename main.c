/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:40:24 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/02 22:25:41 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./mlx/mlx.h"

void print_map_info(t_data *data)
{
	// PRINT PARSING
	printf("texture : \n");
	for (int i = 0; i < 4; i++)
		printf("texture[%d] : %s\n", i, data->map.texture[i]);
	printf("colors :\n");
	printf("F : %d %d %d\n", data->map.col[0][0], data->map.col[0][1], data->map.col[0][2]);
	printf("C : %d %d %d\n", data->map.col[1][0], data->map.col[1][1], data->map.col[1][2]);
	printf("\nmap : (%d,%d)\n", data->map.n, data->map.m);
	for (int i = 0; i < data->map.n; i++)
	{
		for (int j = 0; j < data->map.m; j++)
			printf("%c", (data->map.grid[i][j] >= 0 ? data->map.grid[i][j] + '0' : ' '));
		printf("\n");
	}
	printf("\nstart : %d %d (%d)\n", data->map.start[0], data->map.start[1], data->map.start[2]);
}

void free_all(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	if (data->mini_map.img)
		mlx_destroy_image(data->mlx, data->mini_map.img);
	mlx_destroy_window(data->mlx, data->win);
}

void game_loop(t_data *data)
{
	mlx_hook(data->win, 2, 1 << 0, key_press, data);
	mlx_hook(data->win, 3, 1 << 1, key_release, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_loop_hook(data->mlx, game, data);
	mlx_loop(data->mlx);
}

int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
	{
		printf("invalid number of arg\n");
		return (0);
	}
	init_data(&data);
	if (!parse(&data, av[1]))
		return (0);
	init_player(&data, "12100121");
	print_map_info(&data);
	init_mlx(&data);
	init_textures(&data);
	init_map(&data);
	init_sprite(&data);
	game_loop(&data);
}
