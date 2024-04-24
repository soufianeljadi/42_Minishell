NAME = pipex

CC = cc 

CFLAGS = -Wall -Wextra -Werror

SRC = utils1.c \
	  utils2.c \
	  utils3.c \
	  pipex.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

all: $(NAME)

%.o : %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
