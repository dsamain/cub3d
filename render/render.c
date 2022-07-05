/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:04:41 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/03 15:22:56 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_floor_ceil(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (i < data->height / 2)
				my_mlx_pixel_put(data, j, i, get_trgb(0, data->map.col[1][0],
						data->map.col[1][1], data->map.col[1][2]));
			else
				my_mlx_pixel_put(data, j, i, get_trgb(0, data->map.col[0][0],
						data->map.col[0][1], data->map.col[0][2]));
			j++;
		}
		i++;
	}
}

void	render_ray(t_data *data, t_ray *ray, int x)
{
	int	i;

	setup_ray(data, ray, x);
	add_wall_dist(data, ray);
	i = ft_max(0, ray->start);
	while (i < ft_min(ray->end, data->height))
		draw_pixel(data, ray, i++, x);
	free_ray(ray);
	return ;
}

void	render_view(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < data->width)
	{
		ray.pos = data->player.pos;
		init_ray(data, &ray, data->player.dir, x);
		if (!ray_cast(data, &ray))
			continue ;
		render_ray(data, &ray, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
