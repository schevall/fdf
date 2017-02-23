# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schevall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/13 17:35:39 by schevall          #+#    #+#              #
#    Updated: 2017/02/23 19:38:26 by schevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
FLAG = -Wall -Wextra -Werror
OPTION = -c
SRC = main_fdf.c\
	  fdf_error.c\
	  parsing.c\
	  display.c\
	  get_coord.c\
	  color.c\

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
OBJ_PATH = obj/

$(NAME): $(OBJ)
	@make -C ./libft/
	@gcc -o $(NAME) -L ./libft/ -lft -L ./libft/printf/ -lftprintf -lm -lmlx \
		-framework OpenGL -framework AppKit  $(FLAG) $(OBJ)

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj
	@gcc -c $(FLAG) -o $@ $<

clean:
	@make clean -C ./libft/
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make fclean -C ./libft/
	@/bin/rm -f $(NAME)

re: fclean all
