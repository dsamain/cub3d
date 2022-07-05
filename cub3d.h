/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:00:05 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/04 12:16:39 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 640
# define HEIGHT 440
# define BUFF_SZ 10000
# define INF 1000000000

# define SPEED 0.20
# define R_SPEED 0.08
# define MAX_SPEED 0.4
# define ACC 0.05
# define SENSITIVITY 777

# define MAP_RANGE 10

# define MAX_PORTAL 20

# define SS 2
# define SPRITE_SIZE 12
# define FRAME_DURATION 4

# define ESC 53
# define KEY_SPACE 49
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_O 31
# define KEY_P 35
# define KEY_M 46
# define KEY_SHIFT 257

typedef struct s_node {
	void			*elem;
	struct s_node	*next;
}	t_node;

typedef struct s_map {
	int		n;
	int		m;
	int		**grid;
	int		start[3];
	char	*texture[4];
	int		col[2][3];
}	t_map;

typedef struct s_pos {
	double	x;
	double	y;
}	t_pos;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pix;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_portal {
	t_pos	pos;
	int		ori;
}	t_portal;

typedef struct s_ray {
	t_pos			pos;
	t_pos			dir;
	double			dx;
	double			dy;
	double			side_dist_x;
	double			side_dist_y;
	double			wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				map_x;
	int				map_y;
	int				side;
	int				line_height;
	double			wall_x;
	double			y_step;
	int				text_x;
	int				i;
	t_image			*texture;
	int				start;
	int				end;
	struct s_ray	*next;
	int				cnt;
}	t_ray;

typedef struct s_player {
	t_pos	pos;
	t_pos	dir;
	t_pos	plane;
	double	angle;
	int		fov;
	int		move_left;
	int		move_right;
	int		move_up;
	int		move_down;
	int		rotate_left;
	int		rotate_right;
	double	vel_l;
	double	vel_r;
	double	vel_u;
	double	vel_d;
}	t_player;

typedef struct s_keys {
	int	w;
	int	a;
	int	s;
	int	d;
}	t_keys;

typedef struct s_data {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pix;
	int				line_length;
	int				endian;
	int				height;
	int				width;
	int				toogle_minimap;
	int				free_mouse;
	int				sprite_cnt;
	t_map			map;
	t_player		player;
	t_node			*garbage;
	t_keys			keys;
	t_image			texture[4];
	t_image			mini_map;
	t_image			sprite[SPRITE_SIZE];
	t_image			sprite_buff;
	t_portal		portal[2];
}	t_data;

void			draw_pixel(t_data *data, t_ray *ray, int i, int x);

//game
void			game_loop(t_data *data);
int				game(void *void_data);

//render
void			render_view(t_data *data);
void			render_floor_ceil(t_data *data);

//draw
void			draw_pixel(t_data *data, t_ray *ray, int i, int x);

//utils
int				ft_abs(int n);
int				ft_strlen(char *s);
char			*ft_join(t_data *data, char *s1, char *s2);
double			dist(double x1, double x2, double y1, double y2);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
double			ft_fmax(double a, double b);
double			ft_fmin(double a, double b);
int				ft_strcmp(const char *s1, const char *s2);

//mlx utils
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_pixel_put(t_image *img, int x, int y, int color);
unsigned int	get_trgb(int t, int r, int g, int b);
unsigned int	get_pixel(t_data *data, t_image *texture, int x, int y);
void			clear_image(t_image *img);

//init
void			init_data(t_data *data);
void			init_player(t_data *data, char *dir);
void			init_mlx(t_data *data);
void			init_image(t_data *data, t_image *img, char *path);
void			init_textures(t_data *data);
void			init_map(t_data *data);
void			init_sprite(t_data *data);
void			init_image_null(t_data *data);

void			free_all(t_data *data);

int				game(void *void_data);
void			put_back_ground(t_data *data);
void			update(t_data *data, t_player *player);

//sprite
void			init_sprite(t_data *data);
void			rescale_image(t_data *data, t_image *src, t_image *dest);
void			render_gun(t_data *data);

//ray cast
int				ray_cast(t_data *data, t_ray *ray);
int				is_portal(t_data *data, t_ray *ray);
void			init_ray(t_data *data, t_ray *ray, t_pos dir, int x);
void			setup_ray(t_data *data, t_ray *ray, int x);
void			add_wall_dist(t_data *data, t_ray *ray);
void			free_ray(t_ray *ray);
int				get_text_x(t_data *data, t_ray *ray, t_image *texture);

//portal
int				is_portal(t_data *data, t_ray *ray);
t_pos			get_new_ray_dir(t_pos *dir, int ori1, int ori2);
void			manage_portal(t_data *data, t_ray *ray, int col);
void			adjust_pos(t_portal *portal, t_ray *ray,
					t_pos *pos, double *wall_x);
t_pos			get_new_ray_pos(t_ray *ray,
					t_portal *portal, t_portal *other_portal);

//hook
int				keyHook(int keyCode, void *void_data);
int				mouse_hook(int keycode, int x, int y, void *void_data);
int				key_press(int keyCode, void *void_data);
int				key_release(int keyCode, void *void_data);

//action
void			move_player(t_data *data, t_player *player);
void			rotate_player(t_data *data, t_player *player);
void			set_portal(t_data *data, t_player *player, int col);
int				teleporte(t_data *data, t_player *player, t_pos *v, int col);
void			collision(t_data *data, t_player *player, t_pos *v);

//parse
int				parse(t_data *data, char *path);

//	info_parse
int				get_id(char *rm);
int				parse_texture_path(t_data *data, char **dest, char **raw_map);
int				parse_rgb(int *dest, char **raw_map);
int				get_info(t_data *data, char **raw_map);

//	map_parse
int				check_valid(char *raw_map);
void			get_dim(t_data *data, char *raw_map);
int				alloc_map(t_data *data);
int				get_orientation(char c);
int				parse_map(t_data *data, char **raw_map, int i, int j);
int				check_valid_parse_map(char **raw_map, int idx);

//	check border/set start
int				set_start(t_data *data);
int				dfs(t_data *data, int i, int j);
int				check_border(t_data *data);

//	minimap

void			init_map(t_data *data);
void			minimap(t_data *data, t_image *map);

//garbage
void			*ft_malloc(t_data *data, int size);
int				g_push(t_node **garbage, void *elem);
t_node			*create_node(void *new_elem);
void			g_print(t_node *garbage);
int				g_clear(t_data *data, t_node **garbage, char *msg);

#endif