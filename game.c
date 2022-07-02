/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:13:46 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/02 23:16:04 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rescale_image(t_data *data, t_image *src, t_image *dest)
{
	double	x;
	double	y;
	int		i;
	int		j;
	unsigned int	col;

	i = 0;
	while (i < dest->height)
	{
	j = 0;
		while (j < dest->width)
		{
			col = get_pixel(data, src, (double)j / dest->width * src->width, (double)i / dest->height * src->height);
			ft_pixel_put(dest, j, i, col);
			j++;
		}
		i++;
	}
}

void render_gun(t_data *data)
{
	//mlx_put_image_to_window(data->mlx, data->win, data->sprite[rand()%12].img, data->width - data->sprite[0].width, data->height - data->sprite[0].height);
	int	idx;

	idx = data->sprite_cnt / FRAME_DURATION;
	printf("idx : %d\n", idx);
	mlx_put_image_to_window(data->mlx, data->win, data->sprite[idx].img, data->width - data->sprite[idx].width, data->height - data->sprite[idx].height);
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
	update_player(data, &data->player);
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
