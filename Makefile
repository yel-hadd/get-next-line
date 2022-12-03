# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 00:42:22 by yel-hadd          #+#    #+#              #
#    Updated: 2022/12/03 00:45:31 by yel-hadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
SRC := get_next_line_utils.c \
	get_next_line_utils.c

OBJ = $(SRC:c=o)
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) 
	@ar rc $(NAME) $(OBJ)

%.o : %.c getnextline.h
	@cc ${CFLAGS} -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus