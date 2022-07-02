/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 23:12:21 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/02 19:22:55 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
		if (s1[i] != s2[i])
			return (1);
	return (s2[i]);
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
