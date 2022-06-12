/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:42:10 by dsamain           #+#    #+#             */
/*   Updated: 2022/05/01 22:08:46 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_raw(t_data *data, char *path)
{
	char	*raw;
	char	*buff;
	int		stat;
	int		fd;

	fd = open(path, O_RDONLY);
	buff = ft_malloc(data, sizeof(char) * (BUFF_SZ + 1));
	raw = NULL;
	if (fd <= 0 || !buff)
		return (NULL);
	while (1)
	{
		stat = read(fd, buff, BUFF_SZ);
		if (stat < 0)
			return (NULL);
		if (!stat)
			return (raw);
		buff[stat] = 0;
		raw = ft_join(data, raw, buff);
		if (!raw)
			return (NULL);
	}
	return (NULL);
}

int	parse(t_data *data, char *path)
{
	char	*raw_map;

	raw_map = get_raw(data, path);
	if (!raw_map)
		return (g_clear(&data->garbage, "error while reading"));
	if (!get_info(data, &raw_map))
		return (g_clear(&data->garbage, "error while info parsing"));
	if (!parse_map(data, &raw_map))
		return (g_clear(&data->garbage, "error while map parsing"));
	if (!set_start(data))
		return (g_clear(&data->garbage, "invalid/missing start"));
	if (!check_border(data))
		return (g_clear(&data->garbage, "no border"));
	return (1);
}
