/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:07:22 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/01 22:19:38 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_fmax(double a, double b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_join(t_data *data, char *s1, char *s2)
{
	char	*out;
	int		sz1;
	int		sz2;
	int		i;
	int		j;

	sz1 = ft_strlen(s1);
	sz2 = ft_strlen(s2);
	out = ft_malloc(data, sz1 + sz2 + 1);
	if (!out)
		return (NULL);
	i = -1;
	while (++i < sz1)
		out[i] = s1[i];
	j = -1;
	while (++j < sz2)
		out[i + j] = s2[j];
	out[i + j] = 0;
	return (out);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
