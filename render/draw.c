/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:19:36 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/03 15:03:53 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_portal_pixel(t_data *data, t_ray *ray, int x, int i)
{
	if (is_portal(data, ray) == 0)
		my_mlx_pixel_put(data, x, i, get_trgb(0, 50, 128, 255));
	else
		my_mlx_pixel_put(data, x, i, get_trgb(0, 255, 128, 50));
}

unsigned int	get_pixel_col(t_ray *ray, int pos)
{
	return (*(unsigned int *)(ray->texture->addr
		+ (int)pos * ray->texture->line_length
		+ ray->text_x * (ray->texture->bits_per_pix) / 8));
}

void	draw_pixel(t_data *data, t_ray *ray, int i, int x)
{
	double			pos;
	double			diff;
	double			sin;

	if (i < ray->start || i >= ray->end)
		return ;
	pos = ray->y_step * (double)(i - (double)ray->start);
	diff = fabs((double)ray->text_x - (double)(ray->texture->width / 2))
		/ (ray->texture->width / 2) * 1.7;
	sin = sqrt(1 - diff * diff) * 0.9;
	if (pos < sin * ray->texture->height
		&& pos > ray->texture->height - (sin * ray->texture->height)
		&& is_portal(data, ray) != -1)
	{
		if (data->portal[0].ori != -1
			&& data->portal[1].ori != -1 && ray->next)
			draw_pixel(data, ray->next, i, x);
		else
			put_portal_pixel(data, ray, x, i);
		if (pos > sin * ray->texture->height * 0.96 || pos
			< ray->texture->height - (sin * ray->texture->height * 0.96))
			put_portal_pixel(data, ray, x, i);
		return ;
	}
	my_mlx_pixel_put(data, x, i, get_pixel_col(ray, pos));
}

void	draw_line(t_data *data, t_ray *ray, t_image *texture, int x)
{
	unsigned int	col;
	double			y_step;
	double			pos;
	int				text_x;
	int				i;

	text_x = get_text_x(data, ray, texture);
	y_step = (double)texture->height / (double)ray->line_height;
	i = -ray->line_height / 2 + data->height / 2;
	pos = 0;
	if (i < 0)
	{
		pos = -i * y_step;
		i = 0;
	}
	while (i < ft_min(data->height, data->height / 2 + ray->line_height / 2))
	{
		col = *(unsigned int *)(texture->addr + (int)pos
				* texture->line_length + text_x * (texture->bits_per_pix) / 8);
		pos += y_step;
		if ((col >> 24) != 255)
			my_mlx_pixel_put(data, x, i, col);
		i++;
	}
}
