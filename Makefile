# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cheller <cheller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 19:02:56 by cheller           #+#    #+#              #
#    Updated: 2021/01/08 18:48:19 by cheller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRC_FOLDER = srcs/
SRC =	$(SRC_FOLDER)main.c \
		$(SRC_FOLDER)md5/md5_help.c \
		$(SRC_FOLDER)md5/md5.c \
		$(SRC_FOLDER)sha/sha256_help.c \
		$(SRC_FOLDER)sha/sha224.c \
		$(SRC_FOLDER)sha/sha256.c \
		$(SRC_FOLDER)sha/sha512_help.c \
		$(SRC_FOLDER)sha/sha512.c \
		$(SRC_FOLDER)help/printing.c \
		$(SRC_FOLDER)help/help.c \
		$(SRC_FOLDER)help/help2.c \
		$(SRC_FOLDER)help/handlers.c \
		$(SRC_FOLDER)help/readers.c

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	gcc -I ./include -I ./libftprintf $(FLAGS) -c -o $@ $^

$(NAME): $(OBJ)
	@make -C ./libftprintf all
	gcc -I ./include/ -I ./libftprintf -o $(NAME) $(FLAGS) $(OBJ) -Llibftprintf -lftprintf


clean:
	@rm -f $(OBJ)
	@make -C ./libftprintf clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./libftprintf fclean

re: fclean all