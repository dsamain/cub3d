/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:22:44 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/04 10:38:43 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_sprite_rescaled(t_data *data, t_image *img, char *path)
{
	t_image	tmp;

	init_image(data, &tmp, path);
	img->width = (double)tmp.width * SS;
	img->height = (double)tmp.height * SS;
	img->img = mlx_new_image(data->mlx,
			img->width, img->height);
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pix, &img->line_length, &img->endian);
	rescale_image(data, &tmp, img);
}

void	init_sprite(t_data *data)
{
	get_sprite_rescaled(data, &data->sprite[0], "textures/gun/1.xpm");
	get_sprite_rescaled(data, &data->sprite[1], "textures/gun/12.xpm");
	get_sprite_rescaled(data, &data->sprite[2], "textures/gun/11.xpm");
	get_sprite_rescaled(data, &data->sprite[3], "textures/gun/10.xpm");
	get_sprite_rescaled(data, &data->sprite[4], "textures/gun/9.xpm");
	get_sprite_rescaled(data, &data->sprite[5], "textures/gun/8.xpm");
	get_sprite_rescaled(data, &data->sprite[6], "textures/gun/7.xpm");
	get_sprite_rescaled(data, &data->sprite[7], "textures/gun/6.xpm");
	get_sprite_rescaled(data, &data->sprite[8], "textures/gun/5.xpm");
	get_sprite_rescaled(data, &data->sprite[9], "textures/gun/4.xpm");
	get_sprite_rescaled(data, &data->sprite[10], "textures/gun/3.xpm");
	get_sprite_rescaled(data, &data->sprite[11], "textures/gun/2.xpm");
}

void	rescale_image(t_data *data, t_image *src, t_image *dest)
{
	int				i;
	int				j;

	i = -1;
	while (++i < dest->height)
	{
	j = -1;
		while (++j < dest->width)
			ft_pixel_put(dest, j, i, get_pixel(data, src,
					(double)j / dest->width * src->width,
					(double)i / dest->height * src->height));
	}
}

void	render_gun(t_data *data)
{
	int	idx;

	idx = data->sprite_cnt / FRAME_DURATION;
	mlx_put_image_to_window(data->mlx, data->win, data->sprite[idx].img,
		data->width - data->sprite[idx].width,
		data->height - data->sprite[idx].height);
}
