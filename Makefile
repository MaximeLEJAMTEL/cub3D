CC = cc -Wall -Wextra -Werror -g
NAME = cub3D
HEADER = cub3D.h
LIBFT = src/libft/libft.a
MLX = MacroLibX/libmlx.so
MLXDIR = MacroLibX
SRCS = src/main.c src/hook.c src/ray.c src/move.c src/tex.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(MAKE) -C src/libft
	$(CC) $(OBJS) -o $(NAME) $(LIBFT) $(MLX) -lSDL2 -lm

$(MLX) :
	make -C $(MLXDIR)

%.o : %.c
	$(CC) $< -c -o $@

clean:
	$(MAKE) -C src/libft clean
	$(MAKE) -C $(MLXDIR) clean
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)
	$(MAKE) -C src/libft fclean

re: fclean all

.PHONY: all fclean clean re
