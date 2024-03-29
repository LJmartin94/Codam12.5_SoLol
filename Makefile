# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/09 13:42:12 by limartin      #+#    #+#                  #
#    Updated: 2023/03/30 20:26:55 by limartin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long
MAP = map.ber

MLX_DIR = ./MLX42
MLX_LIB = $(MLX_DIR)/libmlx42.a 
MLX_FLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
MLX_INCL = $(MLX_DIR)/include/MLX42

SRC_DIR = ./src

all: $(NAME)

$(NAME): leon proud
	gcc -o $(NAME) $(SRC_DIR)/*.c $(MLX_LIB) $(MLX_FLAGS) -I $(MLX_INCL)

run: $(NAME)
	./$(NAME) $(MAP)

leon proud:
	@if [ ! -d $(MLX_DIR) ]; \
	then git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); fi
	cd $(MLX_DIR) && cmake . && make

clean:
	@cd $(MLX_DIR) cmake clean
	# @$(MAKE) clean -C $(MLX_DIR)
	rm -rf *.o

fclean: clean
	@cd $(MLX_DIR) cmake fclean -C 
	# @$(MAKE) fclean -C $(MLX_DIR)
	rm -rf $(MLX_DIR)
	rm -rf $(NAME)

re: fclean all