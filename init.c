/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:04:42 by dsamain           #+#    #+#             */
/*   Updated: 2022/05/07 17:05:46 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	int	i;

	data->width = WIDTH;
	data->height = HEIGHT;
	data->img = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->addr = NULL;
	data->garbage = NULL;
	i = -1;
	while (++i < 4)
		data->map.texture[i] = NULL;
	i = -1;
	data->map.col[0][0] = -1;
	data->map.col[1][0] = -1;
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->mini_map.img = NULL;
	data->mini_map.addr = NULL;
	data->mini_map.width = data->width / 5;
	data->mini_map.height = data->width / 5;
	data->portal[0].ori = -1;
	data->portal[1].ori = -1;
}

void	init_player(t_data *data, char *dir)
{
	data->player.pos.x = data->map.start[1] + 0.5;
	data->player.pos.y = data->map.start[0] + 0.5;
	data->player.dir.x = dir[data->map.start[2]] - '0' - 1;
	data->player.dir.y = dir[data->map.start[2] + 4] - '0' - 1;
	data->player.plane.x = data->player.dir.y * 0.66;
	data->player.plane.y = -data->player.dir.x * 0.66;
	data->player.angle = 0;
	data->player.move_up = 0;
	data->player.move_down = 0;
	data->player.move_left = 0;
	data->player.move_right = 0;
	data->player.rotate_left = 0;
	data->player.rotate_right = 0;
	data->player.vel_l = 0;
	data->player.vel_r = 0;
	data->player.vel_u = 0;
	data->player.vel_d = 0;
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3d");
	data->img = NULL;
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pix,
			&data->line_length, &data->endian);
}

void	init_textures(t_data *data)
{
	int	i;
	int	sz;

	i = 0;
	while (i < 4)
	{
		//sz = ft_strlen(data->map.texture[i]);
		//if (sz >= 4 && !ft_strcmp(data->map.texture[i] + sz - 4, ".xpm"))
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx,
				data->map.texture[i], &data->texture[i].width,
				&data->texture[i].height);
		//mlx_png_file_to_image()
		//if (sz >= 4 && !ft_strcmp(data->map.texture[i] + sz - 4, ".png"))
			//data->texture[i].img = mlx_png_file_to_image(data->mlx,
					//data->map.texture[i], &data->texture[i].width,
					//&data->texture[i].height);
		if (!data->texture[i].img)
		{
			g_clear(&data->garbage, "");
			printf("Error while reading texture\n");
			exit(1);
		}
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
				&data->texture[i].bits_per_pix, &data->texture[i].line_length,
				&data->texture[i].endian);
		i++;
	}
}