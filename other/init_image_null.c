/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:52:46 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/03 17:55:20 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_image_null(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		data->texture[i].img = NULL;
	i = -1;
	while (++i < SPRITE_SIZE)
		data->sprite[i].img = NULL;
}
