/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:38:31 by dsamain           #+#    #+#             */
/*   Updated: 2022/05/03 14:02:29 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dist(double x1, double x2, double y1, double y2)
{
	return (sqrt(fabs(x1 - x2) * fabs(x1 - x2) + fabs(y1 - y2) * fabs(y1 - y2)));
}


int ft_abs(int n)
{
	return (n + 2 * (-n) * (n < 0));
}

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}
double	ft_fmin(double a, double b)
{
	if (a <= b)
		return (a);
	return (b);
}

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

char *ft_join(t_data *data, char *s1, char *s2)
{
	char	*out;
	int		sz1;
	int		sz2;
	int		i;
	int		j;

	sz1 = ft_strlen(s1);
	sz2 = ft_strlen(s2);
	out = ft_malloc(data, sz1+sz2+1);	
	if (!out)
		return (NULL);
	i = -1;	
	while (++i < sz1)
		out[i] = s1[i];
	j = -1;
	while (++j < sz2)
		out[i+j] = s2[j];
	out[i+j] = 0;
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

