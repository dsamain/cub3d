/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:18:03 by dsamain           #+#    #+#             */
/*   Updated: 2022/04/29 10:01:30by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_line(t_data *data, t_ray *ray, t_image *texture, int x)
{
	double	wall_x;
	double	y_step;
	double	pos;
	int		text_x;
	int		i;

	if (ray->side)
		wall_x = data->player.pos.x + ray->dir.x * ray->wall_dist;
	else
		wall_x = data->player.pos.y + ray->dir.y * ray->wall_dist;
	wall_x -= floor(wall_x);
	text_x = wall_x * texture->width;
	if ((!ray->side && ray->dir.x < 0) || (ray->side && ray->dir.y < 0))
		text_x = texture->width - text_x - 1;
	y_step = (double)texture->height / (double)ray->line_height;
	i = -ray->line_height / 2 + data->height / 2;
	pos = 0;
	int start = i, end = data->height / 2 + ray->line_height / 2;
	if (i < 0)
	{
		pos = -i * y_step;
		i = 0;
	}
	while (i < ft_min(data->height, data->height / 2 + ray->line_height / 2))
	{
		unsigned int col = *(unsigned int *)(texture->addr + (int)pos * texture->line_length  + text_x * (texture->bits_per_pix) / 8);
		pos += y_step;
		if ((col >> 24) != 255)
			my_mlx_pixel_put(data, x, i, col);
		i++;
	}
}

void draw_pixel(t_data *data, t_ray *ray, int i, int x)
{
	double	pos;

	if (i < ray->start || i >= ray->end)
		return ;
	pos = (double)(i - (double)ray->start) * ray->y_step;
	double diff = fabs((double)ray->text_x - (double)(ray->texture->width / 2)) / (ray->texture->width / 2) * 1.7;
	double sin = sqrt(1 - diff * diff) * 0.9;
	if (pos < sin * ray->texture->height && pos > ray->texture->height - (sin * ray->texture->height))
	{
		if (is_portal(data, ray) != -1)
		{
			if (data->portal[0].ori != -1 && data->portal[1].ori != -1 && ray->next)
				draw_pixel(data, ray->next, i, x);
			else
			{
				if (is_portal(data, ray) == 0)
					my_mlx_pixel_put(data, x, i, get_trgb(0,50,128,255));
				else
					my_mlx_pixel_put(data, x, i, get_trgb(0,255,128,50));
			}
			if (pos > sin * ray->texture->height * 0.96 || pos < ray->texture->height - (sin * ray->texture->height * 0.96))
			{
				if (is_portal(data, ray) == 0)
					my_mlx_pixel_put(data, x, i, get_trgb(0,50,128,255));
				else
					my_mlx_pixel_put(data, x, i, get_trgb(0,255,128,50));
			}
			return ;
		}

	}
		
	unsigned int col = *(unsigned int *)(ray->texture->addr + (int)pos * ray->texture->line_length  + ray->text_x * (ray->texture->bits_per_pix) / 8);
	if ((col >> 24) != 255)
		my_mlx_pixel_put(data, x, i, col);
	//else if (ray->next && ray->next->hit)
		//draw_pixel(data, ray->next, i, x);
}

void setup_ray(t_data *data, t_ray *ray, int x)
{
	if (!ray->hit)
		return ;
	if (ray->side && ray->dir.y < 0)
		ray->texture = &data->texture[0];
	else if (ray->side && ray->dir.y >= 0)
		ray->texture = &data->texture[2];
	else if (!ray->side && ray->dir.x >= 0)
		ray->texture = &data->texture[3];
	else if (!ray->side && ray->dir.x < 0)
		ray->texture = &data->texture[1];
	if (ray->side)
		ray->wall_x = ray->pos.x + ray->dir.x * ray->wall_dist;
	else
		ray->wall_x = ray->pos.y + ray->dir.y * ray->wall_dist;
	ray->wall_x -= floor(ray->wall_x);
	ray->text_x = ray->wall_x * ray->texture->width;
	if ((!ray->side && ray->dir.x < 0) || (ray->side && ray->dir.y < 0))
		ray->text_x = ray->texture->width - ray->text_x - 1;
	ray->y_step = (double)ray->texture->height / (double)ray->line_height;
	//i = -ray->line_height / 2 + data->height / 2;
	ray->start = -ray->line_height / 2 + data->height / 2;
	ray->end = data->height / 2 + ray->line_height / 2;
	if (ray->next && ray->next->hit)
	{
		setup_ray(data, ray->next, x);
	}
}
void add_wall_dist(t_data *data, t_ray *ray)
{
	while (ray->next)
	{
		ray->next->wall_dist += ray->wall_dist;
		ray->next->line_height = (double)data->height / ray->next->wall_dist;	
		ray->next->start = -ray->next->line_height / 2 + data->height / 2;
		ray->next->end = data->height / 2 + ray->next->line_height / 2;
		ray->next->y_step = (double)ray->next->texture->height / (double)ray->next->line_height;
		ray = ray->next;
	}
}

void free_ray(t_ray *ray)
{
	if (!ray->next)
		return ;
	free_ray(ray->next);
	free(ray->next);
}

void render_ray(t_data *data, t_ray *ray, int x)
{
	setup_ray(data, ray, x);
	add_wall_dist(data, ray);
	for (int i = 0; i < data->height; i++)
		draw_pixel(data, ray, i, x);
	free_ray(ray);
	return ;


	if (ray->hit == 0)
		return ;
	//if (ray->side && ray->dir.y < 0)
		//draw_line(data, ray, &data->texture[0], x);
	//else if (ray->side && ray->dir.y >= 0)
		//draw_line(data, ray, &data->texture[2], x);
	//else if (!ray->side && ray->dir.x >= 0)
		//draw_line(data, ray, &data->texture[3], x);
	//else if (!ray->side && ray->dir.x < 0)
		//draw_line(data, ray, &data->texture[1], x);
	//if (ray->next)
		//render_ray(data, ray->next, x)
}

void render_view(t_data *data)
{
	t_ray	ray;
	int		x;


	x = 0;
	while (x < data->width)
	{
		ray.pos = data->player.pos;
		init_ray(data, &ray, data->player.dir, x);
		if (!ray_cast(data, &ray, data->player.dir, x))	
			continue;
		render_ray(data, &ray, x);
		x++;
	}
}

int game(void *void_data)
{
	t_data *data;

	data = (t_data *)void_data;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);		
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pix, &data->line_length, &data->endian);


	update_player(data, &data->player);
	move_player(data, &data->player);
	rotate_player(data, &data->player);
	render_floor_ceil(data);
	render_view(data);
	//draw_col_line(data, data->width/2, 0.50, get_trgb(0, rand()%255, rand()%255, rand()%255));
	//test(data, &data->texture[0]);

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	//mlx_put_image_to_window(data->mlx, data->win, data->texture[1].img, rand()%10, rand()%10);
	return 1;
}

int key_hook(int keycode, void *void_data)
{
	t_data *data;

	printf("keycode : %d\n", keycode);
	data = (t_data *)void_data;
	if (keycode == 53)
	{
		free_all(data);
		exit(0);
	}
	return (1);
}
