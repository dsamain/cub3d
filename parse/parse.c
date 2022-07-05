/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:42:10 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/05 09:54:04 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_id(char *rm)
{
	if (rm[0] == '\n')
		return (0);
	if (rm[0] == 'F' && rm[1] == ' ')
		return (1);
	if (rm[0] == 'C' && rm[1] == ' ')
		return (2);
	if (rm[0] == 'N' && rm[1] == 'O' && rm[2] == ' ')
		return (3);
	if (rm[0] == 'W' && rm[1] == 'E' && rm[2] == ' ')
		return (4);
	if (rm[0] == 'S' && rm[1] == 'O' && rm[2] == ' ')
		return (5);
	if (rm[0] == 'E' && rm[1] == 'A' && rm[2] == ' ')
		return (6);
	return (-1);
}

int	check_valid_parse_map(char **raw_map, int idx)
{
	while ((*raw_map)[idx])
		if ((*raw_map)[idx++] != '\n')
			return (0);
	return (1);
}

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

	if (ft_strlen(path) < 5 || ft_strcmp(path + ft_strlen(path) - 4, ".cub"))
		return (g_clear(data, &data->garbage, "Error: Invalid file extension"));
	raw_map = get_raw(data, path);
	if (!raw_map)
		return (g_clear(data, &data->garbage, "Error while reading"));
	if (!get_info(data, &raw_map))
		return (g_clear(data, &data->garbage, "Error while info parsing"));
	if (!parse_map(data, &raw_map, -1, 0))
		return (g_clear(data, &data->garbage, "Error while map parsing"));
	if (!set_start(data))
		return (g_clear(data, &data->garbage, "Error: Invalid/missing start"));
	if (!check_border(data))
		return (g_clear(data, &data->garbage, "Error: No border"));
	return (1);
}
