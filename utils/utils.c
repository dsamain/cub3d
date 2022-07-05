/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:38:31 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/03 15:34:09 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	dist(double x1, double x2, double y1, double y2)
{
	return (sqrt(fabs(x1 - x2) * fabs(x1 - x2)
			+ fabs(y1 - y2) * fabs(y1 - y2)));
}

int	ft_abs(int n)
{
	return (n + 2 * (-n) * (n < 0));
}

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
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
