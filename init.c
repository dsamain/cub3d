/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:04:42 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/02 23:18:19 by dsamain          ###   ########.fr       */
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
	data->toogle_minimap = 0;
	data->free_mouse = 1;
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3d");
	data->img = NULL;
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pix,
			&data->line_length, &data->endian);
	mlx_mouse_hide();
}

void	init_image(t_data *data, t_image *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx,
			path, &img->width,
			&img->height);
	if (!img->img)
	{
		g_clear(&data->garbage, "");
		printf("Error while reading image\n");
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pix, &img->line_length,
			&img->endian);
}

void	init_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx,
				data->map.texture[i], &data->texture[i].width,
				&data->texture[i].height);
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

void	get_sprite_rescaled(t_data *data, t_image *img, char *path)
{
	t_image	tmp;

	init_image(data, &tmp, path);
	printf("tmp : %d %d\n", tmp.width, tmp.height);
	img->width = (double)tmp.width * SS;
	img->height = (double)tmp.height * SS;
	img->img = mlx_new_image(data->mlx, img->width, img->height);//tmp.width * SS, tmp.height * SS);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pix, &img->line_length, &img->endian);
	printf("img : %d %d\n", img->width, img->height);
	rescale_image(data, &tmp, img);
}

void	init_sprite(t_data *data)
{
	get_sprite_rescaled(data, &data->sprite[0], "textures/gun/1.xpm");
	get_sprite_rescaled(data, &data->sprite[1], "textures/gun/12.xpm");
	get_sprite_rescaled(data, &data->sprite[2], "textures/gun/11.xpm");
	get_sprite_rescaled(data, &data->sprite[3], "textures/gun/10.xpm");
	get_sprite_rescaled(data, &data->sprite[4], "textures/gun/9.xpm");
	get_sprite_rescaled(data, &data->sprite[5], "textures/gun/8.xpm");
	get_sprite_rescaled(data, &data->sprite[6], "textures/gun/7.xpm");
	get_sprite_rescaled(data, &data->sprite[7], "textures/gun/6.xpm");
	get_sprite_rescaled(data, &data->sprite[8], "textures/gun/5.xpm");
	get_sprite_rescaled(data, &data->sprite[9], "textures/gun/4.xpm");
	get_sprite_rescaled(data, &data->sprite[10], "textures/gun/3.xpm");
	get_sprite_rescaled(data, &data->sprite[11], "textures/gun/2.xpm");
	//get_sprite_rescaled(data, &data->sprite[12], "textures/gun/3.xpm");
	//get_sprite_rescaled(data, &data->sprite[13], "textures/gun/2.xpm");
}