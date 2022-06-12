/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:31:51 by dsamain           #+#    #+#             */
/*   Updated: 2022/05/01 22:08:53 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//-1:error
//0:empty
//1:F
//2:C
//3:N
//4:E
//5:S
//6:W

int	get_id(t_data *data, char *rm)
{
	if (rm[0] == '\n')
		return (0);
	if (rm[0] == 'F' && rm[1] == ' ')
		return (1);
	if (rm[0] == 'C' && rm[1] == ' ')
		return (2);
	if (rm[0] == 'N' && rm[1] == 'O' && rm[2] == ' ')
		return (3);
	if (rm[0] == 'E' && rm[1] == 'A' && rm[2] == ' ')
		return (4);
	if (rm[0] == 'S' && rm[1] == 'O' && rm[2] == ' ')
		return (5);
	if (rm[0] == 'W' && rm[1] == 'E' && rm[2] == ' ')
		return (6);
	return (-1);
}

int	parse_texture_path(t_data *data, char **dest, char **raw_map)
{
	int		sz;
	int		i;

	if (*dest)
		return (0);
	*raw_map += 3;
	sz = 0;
	while ((*raw_map)[sz] != '\n')
		sz++;
	*dest = ft_malloc(data, sizeof(char) * (sz + 1));
	if (!dest)
		return (0);
	i = -1;
	while (++i < sz)
		(*dest)[i] = (*raw_map)[i];
	(*dest)[i] = 0;
	*raw_map += sz + 1;
	return (1);
}

int	parse_rgb(t_data *data, int *dest, char **raw_map)
{
	int	idx;
	int	cur;

	*raw_map += 2;
	if (dest[0] != -1)
		return (0);
	dest[0] = 0;
	dest[1] = 0;
	dest[2] = 0;
	idx = 0;
	while (idx < 3 && **raw_map != '\n')
	{
		if (!(**raw_map >= '0' && **raw_map <= '9') && **raw_map != ',')
			return (0);
		if (**raw_map == ',')
			idx++;
		else
			dest[idx] = dest[idx] * 10 + **raw_map - '0';
		*raw_map += 1;
	}
	if (**raw_map != '\n')
		return (0);
	*raw_map += 1;
	return (1);
}

int	get_info(t_data *data, char **raw_map)
{
	int	cnt;	
	int	id;

	cnt = 0;
	while (cnt < 6)
	{
		id = get_id(data, *raw_map);
		if (id < 0)
			return (0);
		if (!id)
		{
			(*raw_map)++;
			continue ;
		}
		if (id > 2)
			if (!parse_texture_path(data, &data->map.texture[id - 3], raw_map))
				return (0);
		if (id > 0 && id < 3)
			if (!parse_rgb(data, data->map.col[id - 1], raw_map))
				return (0);
		cnt++;
	}
	return (1);
}
