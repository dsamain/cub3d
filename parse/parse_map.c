/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:10:35 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/04 11:05:54 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_valid(char *raw_map)
{
	int	i;

	i = -1;
	while (raw_map[++i])
		if (raw_map[i] != '0' && raw_map[i] != '1' && raw_map[i] != 'N'
			&& raw_map[i] != 'E' && raw_map[i] != 'S' && raw_map[i] != 'W'
			&& raw_map[i] != ' ' && raw_map[i] != '\n')
			return (0);
	return (1);
}

void	get_dim(t_data *data, char *raw_map)
{
	int	mx;
	int	cur;
	int	i;

	data->map.n = 1;
	data->map.m = 0;
	i = -1;
	cur = 0;
	mx = 0;
	while (raw_map[++i])
	{
		if (raw_map[i] == '\n')
		{
			data->map.n++;
			mx = ft_max(mx, cur);
			cur = 0;
		}
		else
			cur++;
	}
	data->map.m = ft_max(cur, mx);
}

int	alloc_map(t_data *data)
{
	int	i;

	data->map.grid = ft_malloc(data, sizeof(int *) * data->map.n);
	if (!data->map.grid)
		return (0);
	i = -1;
	while (++i < data->map.n)
	{
		data->map.grid[i] = ft_malloc(data, sizeof(int) * data->map.m);
		if (!data->map.grid[i])
			return (0);
	}
	return (1);
}

int	get_orientation(char c)
{
	if (c == 'N')
		return (2);
	if (c == 'E')
		return (3);
	if (c == 'S')
		return (4);
	if (c == 'W')
		return (5);
	return (-1);
}

int	parse_map(t_data *data, char **raw_map, int i, int j)
{
	int	idx;
	int	tmp;

	while (**raw_map == '\n')
		(*raw_map)++;
	get_dim(data, *raw_map);
	if (!check_valid(*raw_map) || !alloc_map(data))
		return (0);
	idx = 0;
	tmp = data->map.m - 1;
	while (++i < data->map.n)
	{
		j = -1;
		if ((*raw_map)[idx] == '\n')
			break ;
		while (++j < data->map.m && (*raw_map)[idx] && (*raw_map)[idx] != '\n')
		{
			data->map.grid[i][tmp - j] = get_orientation((*raw_map)[idx]);
			data->map.grid[i][tmp - j] += 2 * ((*raw_map)[idx++] == '1');
		}
		while (j < data->map.m)
			data->map.grid[i][tmp - j++] = -1;
		idx++;
	}
	return (check_valid_parse_map(raw_map, idx));
}
