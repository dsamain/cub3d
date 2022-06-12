//INC=/usr/include


//INCLIB=$(INC)/../lib


NAME= cub3d
SRC = main.c mlx_utils.c utils.c render.c ray_cast.c hook.c action.c init.c garbage.c \
		parse/parse.c parse/parse_map.c parse/parse_info.c parse/border_start.c \
		portal.c

OBJ = $(SRC:%.c=%.o)

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
#FLAGS = -Wall -Wextra -Werror

CC = gcc $(FLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MLXFLAGS)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: clean all

bonus : $(NAME_B)

$(NAME_B) : $(OBJ_B)
	$(CC) -o $(NAME_B) $(OBJ_B) $(MLXFLAGS)
