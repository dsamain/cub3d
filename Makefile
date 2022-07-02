
SRC = main.c game.c mlx_utils.c render.c raycast.c raycast2.c draw.c hook.c action.c action2.c init.c garbage.c \
		parse/parse.c parse/parse_map.c parse/parse_info.c parse/border_start.c \
		utils.c utils2.c portal.c minimap.c

OBJ = $(SRC:%.c=%.o)

OBJ_B = $(SRC:%.c=%.o)

CC = gcc # $(FLAGS)

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX = libmlx.dylib
# FLAGS = -Wall -Wextra -Werror

NAME = cub3d

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	$(CC) -O3 -I. $(MLX) -o $(NAME) $(OBJ) $(MLXFLAGS)

$(MLX):
	@$(MAKE) -C mlx
	@mv mlx/$(MLX) .

clean:
	@$(MAKE) -C mlx clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(MLX)

re: fclean all
