/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:57:22 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/04 10:26:05 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	collision2(t_data *data, t_player *player, t_pos *v)
{
	double	dist;
	double	x;
	double	y;

	x = player->pos.x;
	y = player->pos.y + v->y;
	dist = 1;
	if (data->map.grid[(int)y][(int)x - 1])
		dist = ft_fmin(dist, x - (int)x);
	if (data->map.grid[(int)y][1 + (int)x])
		dist = ft_fmin(dist, ceilf(x) - x);
	if (data->map.grid[(int)y - 1][(int)x])
		dist = ft_fmin(dist, y - (int)y);
	if (data->map.grid[1 + (int)y][(int)x])
		dist = ft_fmin(dist, ceilf(y) - y);
	if (dist <= 0.15)
		v->y = 0;
}

void	collision(t_data *data, t_player *player, t_pos *v)
{
	double	dist;
	double	x;
	double	y;

	x = player->pos.x + v->x;
	y = player->pos.y;
	dist = 1;
	if (data->map.grid[(int)y][(int)x - 1])
		dist = ft_fmin(dist, x - (int)x);
	if (data->map.grid[(int)y][1 + (int)x])
		dist = ft_fmin(dist, ceilf(x) - x);
	if (data->map.grid[(int)y - 1][(int)x])
		dist = ft_fmin(dist, y - (int)y);
	if (data->map.grid[1 + (int)y][(int)x])
		dist = ft_fmin(dist, ceilf(y) - y);
	if (dist <= 0.15)
		v->x = 0;
	collision2(data, player, v);
}
