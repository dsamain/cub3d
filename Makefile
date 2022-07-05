
RENDER_SRC = $(addprefix render/, render.c draw.c raycast.c raycast2.c portal.c sprite.c)
PARSE_SRC = $(addprefix parse/, parse.c parse_map.c parse_info.c border_start.c) 
EVENT_SRC = $(addprefix event/, collision.c hook.c player_event.c portal_event.c update.c)
UTILS_SRC = $(addprefix utils/, mlx_utils.c utils.c utils2.c)
OTHER_SRC = $(addprefix other/, garbage.c init.c init_image_null.c minimap.c)
SRC = main.c game.c

OBJ = 	$(SRC:%.c=%.o) \
		$(RENDER_SRC:%.c=%.o) \
		$(PARSE_SRC:%.c=%.o) \
		$(EVENT_SRC:%.c=%.o) \
		$(UTILS_SRC:%.c=%.o) \
		$(OTHER_SRC:%.c=%.o)

CC = gcc $(FLAGS)

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX = libmlx.dylib
FLAGS = -Wall -Wextra -Werror

NAME = cub3d

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(MLX) -o $(NAME) $(OBJ) $(MLXFLAGS)

$(MLX):
	@$(MAKE) -C mlx
	@mv mlx/$(MLX) .

clean:
	@$(MAKE) -C mlx clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(MLX)

re: fclean all

bonus : all