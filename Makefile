# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/09 13:42:12 by limartin      #+#    #+#                  #
#    Updated: 2022/12/09 14:12:27 by limartin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long
MAP = map.ber
MLX_DIR = ./MLX42

all: $(NAME)

$(NAME): leon proud
	gcc -o $(NAME) *.c

run: $(NAME)
	./$(NAME) $(MAP)

leon proud:
	@if [ ! -d $(MLX_DIR) ]; \
	then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@$(MAKE) -C $(MLX_DIR)

clean:
	@$(MAKE) clean -C $(MLX_DIR)
	rm -rf *.o

fclean: clean
	@$(MAKE) fclean -C $(MLX_DIR)
	rm -rf $(NAME)