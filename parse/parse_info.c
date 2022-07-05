/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:31:51 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/04 10:23:42 by dsamain          ###   ########.fr       */
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

int	parse_texture_path(t_data *data, char **dest, char **raw_map)
{
	int		sz;
	int		i;

	if (*dest)
		return (0);
	*raw_map += 2;
	while (**raw_map == ' ')
		*raw_map += 1;
	sz = 0;
	while ((*raw_map)[sz] != '\n')
		sz++;
	if (!sz)
		return (0);
	*dest = ft_malloc(data, sizeof(char) * (sz + 1));
	if (!dest)
		return (0);
	i = -1;
	while (++i < sz)
		(*dest)[i] = (*raw_map)[i];
	(*dest)[i] = 0;
	while (--i >= 0 && (*dest)[i] == ' ')
		(*dest)[i] = 0;
	*raw_map += sz + 1;
	return (1);
}

int	parse_rgb_sep(char **raw_map)
{
	int	comma_cnt;

	comma_cnt = 0;
	while (**raw_map == ' ' || **raw_map == ',')
	{
		comma_cnt += **raw_map == ',';
		*raw_map += 1;
	}
	return (comma_cnt);
}

int	parse_rgb_num(int *col, char **raw_map)
{
	if (!(**raw_map >= '0' && **raw_map <= '9'))
		return (0);
	while (**raw_map >= '0' && **raw_map <= '9')
	{
		*col = *col * 10 + **raw_map - '0';
		*raw_map += 1;
	}
	return (1);
}

int	parse_rgb(int *dest, char **raw_map)
{
	int	idx;
	int	comma_cnt;

	*raw_map += 2;
	dest[0] = 0;
	dest[1] = 0;
	dest[2] = 0;
	if (parse_rgb_sep(raw_map))
		return (0);
	idx = 0;
	while (idx < 3)
	{
		if (!parse_rgb_num(dest + idx, raw_map))
			return (0);
		if (dest[idx] > 255)
			return (0);
		comma_cnt = parse_rgb_sep(raw_map);
		if ((comma_cnt != 1 && idx < 2) || (comma_cnt && idx == 2))
			return (0);
		idx++;
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
		id = get_id(*raw_map);
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
			if (!parse_rgb(data->map.col[id - 1], raw_map))
				return (0);
		cnt++;
	}
	return (1);
}
