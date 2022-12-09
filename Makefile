# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/09 13:42:12 by limartin      #+#    #+#                  #
#    Updated: 2022/12/09 13:45:22 by limartin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long
MAP = map.ber

all: $(NAME)

$(NAME):
	gcc -o $(NAME) *.c && ./$(NAME) $(MAP)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)