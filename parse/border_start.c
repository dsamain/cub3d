/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:38:00 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/01 22:20:25 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	set_start(t_data *data)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = -1;
	while (++i < data->map.n)
	{
		j = -1;
		while (++j < data->map.m)
		{
			if (data->map.grid[i][j] > 1)
			{
				if (flag)
					return (0);
				flag = 1;
				data->map.start[0] = i;
				data->map.start[1] = j;
				data->map.start[2] = data->map.grid[i][j] - 2;
			}
		}
	}
	return (flag);
}

int	dfs(t_data *data, int i, int j)
{
	if (data->map.grid[i][j] != -1)
		return (1);
	if (i == 0 || i == data->map.n - 1 || j == 0 || j == data->map.m - 1)
		return (0);
	data->map.grid[i][j] = 0;
	if (!dfs(data, i + 1, j) || !dfs(data, i - 1, j)
		|| !dfs(data, i, j + 1) || !dfs(data, i, j - 1))
		return (0);
	return (1);
}

int	check_border(t_data *data)
{
	data->map.grid[data->map.start[0]][data->map.start[1]] = -1;
	return (dfs(data, data->map.start[0], data->map.start[1]));
}
