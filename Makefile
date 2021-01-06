NAME = ft_ssl

SRC = main.c md5/md5.c sha256/sha256.c help/help.c

FLAGS = -Wall -Wextra -Werror -I ./include -I ./libft

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	gcc -g -I ./include -I ./libft $(FLAGS) -c -o $@ $^

$(NAME): $(OBJ)
	@make -C ./libft all
	gcc -g -I ./include/ -I ./libft -o $(NAME) $(FLAGS) $(OBJ) -Llibft -lft


clean:
	@rm -f $(OBJ)
	@make -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all