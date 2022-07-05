/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:16:49 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/03 15:22:50 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setup_ray(t_data *data, t_ray *ray, int x)
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
	ray->start = -ray->line_height / 2 + data->height / 2;
	ray->end = data->height / 2 + ray->line_height / 2;
	if (ray->next && ray->next->hit)
	{
		setup_ray(data, ray->next, x);
	}
}

void	add_wall_dist(t_data *data, t_ray *ray)
{
	while (ray->next)
	{
		ray->next->wall_dist += ray->wall_dist;
		ray->next->line_height = (double)data->height / ray->next->wall_dist;
		ray->next->start = -ray->next->line_height / 2 + data->height / 2;
		ray->next->end = data->height / 2 + ray->next->line_height / 2;
		ray->next->y_step = (double)ray->next->texture->height
			/ (double)ray->next->line_height;
		ray = ray->next;
	}
}

void	free_ray(t_ray *ray)
{
	if (!ray->next)
		return ;
	free_ray(ray->next);
	free(ray->next);
}

int	get_text_x(t_data *data, t_ray *ray, t_image *texture)
{
	double	wall_x;
	int		text_x;

	if (ray->side)
		wall_x = data->player.pos.x + ray->dir.x * ray->wall_dist;
	else
		wall_x = data->player.pos.y + ray->dir.y * ray->wall_dist;
	wall_x -= floor(wall_x);
	text_x = wall_x * texture->width;
	if ((!ray->side && ray->dir.x < 0) || (ray->side && ray->dir.y < 0))
		text_x = texture->width - text_x - 1;
	return (text_x);
}

int	is_portal(t_data *data, t_ray *ray)
{
	int	ori;
	int	col;

	if (ray->side && ray->dir.y < 0)
		ori = 0;
	else if (ray->side && ray->dir.y >= 0)
		ori = 2;
	else if (!ray->side && ray->dir.x >= 0)
		ori = 3;
	else if (!ray->side && ray->dir.x < 0)
		ori = 1;
	col = -1;
	if (data->portal[0].pos.x == ray->map_x && data->portal[0].pos.y
		== ray->map_y && data->portal[0].ori == ori)
		col = 0;
	if (data->portal[1].pos.x == ray->map_x && data->portal[1].pos.y
		== ray->map_y && data->portal[1].ori == ori)
		col = 1;
	return (col);
}
