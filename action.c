/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 05:22:18 by dsamain           #+#    #+#             */
/*   Updated: 2022/05/07 15:53:06 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	update_player(t_data *data, t_player *player)
{
	if (player->move_up)
		player->vel_u = ft_fmin(player->vel_u + ACC, MAX_SPEED);
	else
		player->vel_u = ft_fmax(player->vel_u - ACC, 0);
	if (player->move_down)
		player->vel_d = ft_fmin(player->vel_d + ACC, MAX_SPEED);
	else
		player->vel_d = ft_fmax(player->vel_d - ACC, 0);
	if (player->move_left)
		player->vel_l = ft_fmin(player->vel_l + ACC, MAX_SPEED);
	else
		player->vel_l = ft_fmax(player->vel_l - ACC, 0);
	if (player->move_right)
		player->vel_r = ft_fmin(player->vel_r + ACC, MAX_SPEED);
	else
		player->vel_r = ft_fmax(player->vel_r - ACC, 0);
}

int	close_to_portal(t_data *data, t_pos *pos)
{
	if (data->portal[0].ori == -1 || data->portal[1].ori == -1)
		return (-1);
	if (data->portal[0].ori == 2 && fabs(pos->x - (data->portal[0].pos.x + 0.5)) < 0.2 && fabs(pos->y - data->portal[0].pos.y) <= 0.15)
		return (0);
	if (data->portal[0].ori == 0 && fabs(pos->x - (data->portal[0].pos.x + 0.5)) < 0.2 && fabs(pos->y - (data->portal[0].pos.y + 1)) <= 0.15)
		return (0);
	if (data->portal[0].ori == 1 && fabs(pos->y - (data->portal[0].pos.y + 0.5)) < 0.2 && fabs(pos->x - (data->portal[0].pos.x + 1)) <= 0.15)
		return (0);
	if (data->portal[0].ori == 3 && fabs(pos->y - (data->portal[0].pos.y + 0.5)) < 0.2 && fabs(pos->x - (data->portal[0].pos.x)) <= 0.15)
		return (0);
	if (data->portal[1].ori == 2 && fabs(pos->x - (data->portal[1].pos.x + 0.5)) < 0.2 && fabs(pos->y - data->portal[1].pos.y) <= 0.15)
		return (1);
	if (data->portal[1].ori == 0 && fabs(pos->x - (data->portal[1].pos.x + 0.5)) < 0.2 && fabs(pos->y - (data->portal[1].pos.y + 1)) <= 0.15)
		return (1);
	if (data->portal[1].ori == 1 && fabs(pos->y - (data->portal[1].pos.y + 0.5)) < 0.2 && fabs(pos->x - (data->portal[1].pos.x + 1)) <= 0.15)
		return (1);
	if (data->portal[1].ori == 3 && fabs(pos->y - (data->portal[1].pos.y + 0.5)) < 0.2 && fabs(pos->x - (data->portal[1].pos.x)) <= 0.15)
		return (1);
	return (-1);
}

int teleporte(t_data *data, t_player *player, t_pos *v)
{
	double	dist;
	double	gap;
	t_pos	pos;
	int		col;

	pos.x = player->pos.x + v->x;
	pos.y = player->pos.y + v->y;
	col = close_to_portal(data, &pos);
	if (col == -1)
		return (0);
	player->dir = get_new_ray_dir(data, &player->dir, data->portal[col].ori, data->portal[!col].ori + 2);
	if (data->portal[col].ori == 0 || data->portal[col].ori == 2)
		gap = fabs(data->portal[col].pos.x - pos.x);
	else
		gap = fabs(data->portal[col].pos.y - pos.y);
	if (data->portal[!col].ori == 0)
	{
		player->pos.y = data->portal[!col].pos.y + 1.16;
		if (data->portal[col].ori == 2 || data->portal[col].ori == 1)
			player->pos.x = data->portal[!col].pos.x + gap;
		else
			player->pos.x = data->portal[!col].pos.x + 1 - gap;
	}
	if (data->portal[!col].ori == 2)
	{
		player->pos.y = data->portal[!col].pos.y - 0.16;
		if (data->portal[col].ori == 0 || data->portal[col].ori == 3)
			player->pos.x = data->portal[!col].pos.x + gap;
		else
			player->pos.x = data->portal[!col].pos.x + 1 - gap;
	}
	if (data->portal[!col].ori == 1)
	{
		player->pos.x = data->portal[!col].pos.x + 1.16;
		if (data->portal[col].ori == 0 || data->portal[col].ori == 3)
			player->pos.y = data->portal[!col].pos.y + gap;
		else
			player->pos.y = data->portal[!col].pos.y + 1 - gap;
	}
	if (data->portal[!col].ori == 3)
	{
		player->pos.x = data->portal[!col].pos.x - 0.16;
		if (data->portal[col].ori == 2 || data->portal[col].ori == 1)
			player->pos.y = data->portal[!col].pos.y + gap;
		else
			player->pos.y = data->portal[!col].pos.y + 1 - gap;
	}
	return (1);
}

void	collision(t_data *data, t_player *player, t_pos *v)
{
	double	dist;
	double	x;
	double	y;

	x = player->pos.x + v->x;
	y = player->pos.y;
	dist = 1;
	if (data->map.grid[(int)y][(int)x-1])
		dist = ft_fmin(dist, x - (int)x);
	if (data->map.grid[(int)y][1 + (int)x])
		dist = ft_fmin(dist, ceilf(x) - x);
	if (data->map.grid[(int)y-1][(int)x])
		dist = ft_fmin(dist, y - (int)y);
	if (data->map.grid[1 + (int)y][(int)x])
		dist = ft_fmin(dist, ceilf(y) - y);
	if (dist <= 0.15)
		v->x = 0;
	x = player->pos.x;
	y = player->pos.y + v->y;
	dist = 1;
	if (data->map.grid[(int)y][(int)x-1])
		dist = ft_fmin(dist, x - (int)x);
	if (data->map.grid[(int)y][1 + (int)x])
		dist = ft_fmin(dist, ceilf(x) - x);
	if (data->map.grid[(int)y-1][(int)x])
		dist = ft_fmin(dist, y - (int)y);
	if (data->map.grid[1 + (int)y][(int)x])
		dist = ft_fmin(dist, ceilf(y) - y);
	if (dist <= 0.15)
		v->y = 0;
}

void move_player(t_data *data, t_player *player)
{
	double 	px;
	double 	py;
	t_pos	v;
	int		div;

	px = player->pos.x;
	py = player->pos.y;
	div = 1 + (((player->move_down || player->move_up) + (player->move_left || player->move_right) == 2)
		&& (player->move_down + player->move_up + player->move_left + player->move_right == 2));
	v.y = SPEED * player->dir.y / div * player->vel_u
	- SPEED * player->dir.y / div * player->vel_d
	+ SPEED * player->dir.x / div * player->vel_l
	- SPEED * player->dir.x / div * player->vel_r;
	v.x = SPEED * player->dir.x / div * player->vel_u
	- SPEED * player->dir.x / div * player->vel_d
	+ SPEED * -player->dir.y / div * player->vel_l
	- SPEED * -player->dir.y / div * player->vel_r;
	if ((v.x || v.y) && teleporte(data, player, &v))
		return ;
	collision(data, player, &v);
	player->pos.x += v.x;
	player->pos.y += v.y;
}

void rotate_player(t_data *data, t_player *player)
{
	double	angle;
	double	tmpx;
	double	tmpy;

	angle = player->rotate_left * R_SPEED - player->rotate_right * R_SPEED;
	tmpx = data->player.dir.x;
	tmpy = data->player.dir.y;
	data->player.dir.x = cos(angle) * tmpx - sin(angle) * tmpy;
	data->player.dir.y = sin(angle) * tmpx + cos(angle) * tmpy;
	data->player.plane.x = data->player.dir.y * 0.66;
	data->player.plane.y = -data->player.dir.x * 0.66;
}

void	set_portal(t_data *data, t_player *player, int col)
{
	t_ray	ray;

	ray.pos = player->pos;
	init_ray(data, &ray, player->dir, data->width / 2);
	ray_cast(data, &ray, player->dir, data->width / 2);
	printf("col : %d\n", col);
	printf("portal x y : %d %d\n", ray.map_x, ray.map_y);
	if (ray.side && ray.dir.y < 0)
		data->portal[col].ori = 0;
	else if (ray.side && ray.dir.y >= 0)
		data->portal[col].ori = 2;
	else if (!ray.side && ray.dir.x >= 0)
		data->portal[col].ori = 3;
	else if (!ray.side && ray.dir.x < 0)
		data->portal[col].ori = 1;
	data->portal[col].pos.x = ray.map_x;
	data->portal[col].pos.y = ray.map_y;
	if (data->portal[col].pos.x == data->portal[!col].pos.x
			&&  data->portal[col].pos.y == data->portal[!col].pos.y
			&& data->portal[col].ori == data->portal[!col].ori)
		data->portal[!col].ori = -1;
	printf("portal set at %f %f on the side %d\n", data->portal[col].pos.x, data->portal[col].pos.y, data->portal[col].ori);
}