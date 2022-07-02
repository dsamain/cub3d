/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:46:23 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/02 22:50:42 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pix / 8));
	*(unsigned int *)dst = color;
}

void	ft_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pix / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel(t_data *data, t_image *texture, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return (0);
	return (*(unsigned int *)(texture->addr
		+ (int)y * texture->line_length
		+ x * (texture->bits_per_pix) / 8));
}


unsigned int	get_trgb(int t, int r, int g, int b)
{
	return ((t << 24) + (r << 16) + (g << 8) + b);
}

void	clear_image(t_image *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			ft_pixel_put(img, j, i, 0);
			j++;
		}
		i++;
	}
}