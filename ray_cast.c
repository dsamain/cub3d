/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:37:22 by dsamain           #+#    #+#             */
/*   Updated: 2022/05/07 17:01:06 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	init_ray(t_data *data, t_ray *ray, t_pos dir, int x)
{
	double	cam_x;

	cam_x = 2 * (double)x / (double)data->width - 1;
	ray->dir.x = dir.x + data->player.plane.x * cam_x;
	ray->dir.y = dir.y + data->player.plane.y * cam_x;
	ray->hit = 0;
	ray->map_x = ray->pos.x;
	ray->map_y = ray->pos.y;
	if (ray->dir.x == 0)
		ray->dx = INF;
	else
		ray->dx = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->dy = INF;
	else
		ray->dy = fabs(1 / ray->dir.y);
	ray->next = NULL;
	ray->cnt = 0;
	ray->wall_dist = 0;
}

void	set_side_dist(t_data *data, t_ray *ray, int x) {

	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = ((double)ray->pos.x - (double)ray->map_x) * ray->dx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((double)ray->map_x + 1.0 - ray->pos.x) * ray->dx;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos.y - (double)ray->map_y) * ray->dy;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((double)ray->map_y + 1.0 - ray->pos.y) * ray->dy;
	}
}

int	is_out(t_data *data, int x, int y)
{
	return (x >= data->map.m || y >= data->map.n || x < 0 || y < 0);
}

int	ray_cast(t_data *data, t_ray *ray, t_pos dir, int x)
{
	//printf("cnt for %d : %d\n", x, cnt++);

	set_side_dist(data, ray, x);
		//DDA
		while (!ray->hit)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->dx;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist_y += ray->dy;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			//if (is_out(data, ray->map_x, ray->map_y))
				//return (1);
			ray->hit = (data->map.grid[ray->map_y][ray->map_x] == 1);
			if (ray->hit)
			{
				if (!ray->side)
					ray->wall_dist += ray->side_dist_x - ray->dx;
				else 
					ray->wall_dist += ray->side_dist_y - ray->dy;
				ray->line_height = (double)data->height / ray->wall_dist;	
				if (is_out(data, ray->map_x, ray->map_y))
					return (1);
				if (is_portal(data, ray) != -1 && data->portal[0].ori != -1 && data->portal[1].ori != -1)
					manage_portal(data, ray, is_portal(data, ray), x);
				//ray->next = new_ray(data, ray);
				//ray = ray->next;
			}
		}
		//wall_dist
		
		return (1);
}
