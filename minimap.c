/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:12:27 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/02 19:23:21 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_image *img, int x, int y,
	unsigned int size)
{
	unsigned int	col;
	int				i;
	int				j;

	col = get_trgb(0, 100, 50, 111);
	i = x - 1;
	while (i < x + size)
	{
		j = y;
		while (j < y + size)
		{
			ft_pixel_put(img, i, j, col);
			j++;
		}
		i++;
	}
}

void	init_map(t_data *data)
{
	data->mini_map.height = data->height / 5;
	data->mini_map.width = data->mini_map.height;
	data->mini_map.img = NULL;
}

void	draw_minimap(t_data *data, t_image *map, int step)
{
	int	i;
	int	j;

	i = -MAP_RANGE - 1;
	while (++i <= MAP_RANGE)
	{
		j = -MAP_RANGE;
		while (j <= MAP_RANGE)
		{
			if (data->player.pos.y + i < 0
				|| data->player.pos.y + i >= data->map.n
				|| data->player.pos.x + j < 0
				|| data->player.pos.x + j >= data->map.m)
			{
				j++;
				continue ;
			}
			if (data->map.grid[(int)data->player.pos.y + i]
				[(int)data->player.pos.x + j])
				draw_square(map, (i + MAP_RANGE / 2) * step,
					(j + MAP_RANGE / 2) * step,
					step);
			j++;
		}
	}
}

void	draw_player(t_data *data, t_image *map)
{
	int	i;
	int	j;

	i = map->height / 2 - 1;
	while (i <= map->height / 2 + 1)
	{
		j = map->width / 2 - 1;
		while (j <= map->width / 2 + 1)
		{
			ft_pixel_put(map, i, j, get_trgb(0, 128, 128, 128));
			j++;
		}
		i++;
	}
}

void	minimap(t_data *data, t_image *map)
{
	unsigned int	col;
	int				step;
	int				i;
	int				j;

	//if (map->img)
		//mlx_destroy_image(data->mlx, map->img);
	if (!map->img)
	{
		map->img = mlx_new_image(data->mlx, map->height, map->width);
		map->addr = mlx_get_data_addr(map->img,
				&map->bits_per_pix, &map->line_length, &map->endian);
	}
	else
		clear_image(map);
	step = data->mini_map.height / MAP_RANGE;
	col = 128;
	draw_minimap(data, map, step);
	draw_player(data, map);
	mlx_put_image_to_window(data->mlx, data->win, data->mini_map.img, 0, 0);
}
