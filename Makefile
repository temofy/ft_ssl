NAME = ft_ssl

SRC = main.c md5/md5.c 

FLAGS = -Wall -Wextra -Werror -I ./include -I ./libft

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	gcc -I ./include -I ./libft -c -o $@ $^

$(NAME): $(OBJ)
	@make -C ./libft all
	gcc  -I ./include/ -I ./libft -L ./libft libft.a  -lcrypto -lm -o $(NAME) $(OBJ)


clean:
	@rm -f $(OBJ)
	@make -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all