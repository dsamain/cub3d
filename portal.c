/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:29:54 by dsamain           #+#    #+#             */
/*   Updated: 2022/05/06 20:18:36 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_portal(t_data *data, t_ray *ray)
{
	int	ori;
	int	col;

	//if (data->portal[0].ori == -1 || data->portal[1].ori == -1)
		//return (-1);
	if (ray->side && ray->dir.y < 0)
		ori = 0;
	else if (ray->side && ray->dir.y >= 0)
		ori = 2;
	else if (!ray->side && ray->dir.x >= 0)
		ori = 3;
	else if (!ray->side && ray->dir.x < 0)
		ori = 1;
	col = -1;
	if (data->portal[0].pos.x == ray->map_x && data->portal[0].pos.y == ray->map_y && data->portal[0].ori == ori)
		col = 0;
	if (data->portal[1].pos.x == ray->map_x && data->portal[1].pos.y == ray->map_y && data->portal[1].ori == ori)
		col = 1;
	return (col);
}

t_pos	get_new_ray_dir(t_data *data, t_pos *dir, int ori1, int ori2)
{
	t_pos	new_dir;
	double	tmp;

	new_dir = *dir;
	while (ori1 % 4 != ori2 % 4)
	{
		tmp = new_dir.x;
		new_dir.x = new_dir.y;
		new_dir.y = -tmp;
		ori1++;
	}
	return (new_dir);
}

void	adjust_pos(t_portal *portal, t_ray *ray, t_pos *pos, double *wall_x)
{
	pos->x = (int)portal->pos.x;
	pos->y = (int)portal->pos.y;
	if (portal->ori == 0)
		pos->y += 1.0001;
	if (portal->ori == 2)
		pos->y -= 0.0001;
	if (portal->ori == 1)
		pos->x += 1.0001;
	if (portal->ori == 3)
		pos->x -= 0.0001;
	if (ray->side)
		*wall_x = ray->pos.x + ray->dir.x * ray->wall_dist;
	else
		*wall_x = ray->pos.y + ray->dir.y * ray->wall_dist;
	*wall_x -= floor(*wall_x);
}

t_pos	get_new_ray_pos(t_data *data, t_ray *ray, t_portal *portal, t_portal *other_portal)
{
	t_pos	pos;
	double	wall_x;

	adjust_pos(portal, ray, &pos, &wall_x);
	if (portal->ori == 0) {
		if (other_portal->ori == 2 || other_portal->ori == 1)
			pos.x += wall_x;
		else
			pos.x += 1 - wall_x;
	}
	else if (portal->ori == 1) {
		if (other_portal->ori == 3 || other_portal->ori == 0)
			pos.y += wall_x;
		else
			pos.y += 1 - wall_x;
	}
	else if (portal->ori == 2) {
		if (other_portal->ori == 0 || other_portal->ori == 3)
			pos.x += wall_x;
		else
			pos.x += 1 - wall_x;
	}
	else if (portal->ori == 3) {
		if (other_portal->ori == 1 || other_portal->ori == 2)
			pos.y += wall_x;
		else
			pos.y += 1 - wall_x;
	}
	return (pos);
}

void manage_portal(t_data *data, t_ray *ray, int col, int x)
{
	t_ray	*new_ray;


	if (data->portal[0].ori == -1 || data->portal[1].ori == -1 || ray->cnt == MAX_PORTAL)
		return ;
	new_ray = malloc(sizeof(t_ray));
	if (!new_ray) {
		g_clear(&data->garbage, "Malloc error");
		exit(1);
	}
	*new_ray = *ray;
	new_ray->pos = get_new_ray_pos(data, ray, &data->portal[!col], &data->portal[col]);
	new_ray->dir = get_new_ray_dir(data, &ray->dir, data->portal[col].ori, data->portal[!col].ori + 2);
	init_ray(data, new_ray, new_ray->dir, data->width / 2);
	new_ray->cnt = ray->cnt + 1;
	//new_ray->wall_dist = ray->wall_dist;
	ray_cast(data, new_ray, new_ray->dir, 0);
	ray->next = new_ray;
	//printf("old pos %f %f\nnew pos %f %f\n", ray->pos.x, ray->pos.y, new_ray->pos.x, new_ray->pos.y);
}