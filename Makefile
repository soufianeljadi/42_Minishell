# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 23:52:42 by sdiouane          #+#    #+#              #
#    Updated: 2024/03/13 14:10:00 by sel-jadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc #-g -fsanitize=address 
CFLAGS = -Wall -Wextra -Werror 
RDFLAGS = -lreadline
SRC = main.c \
      ft_split.c \
	  lsts.c \
	  prompt.c 

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(RDFLAGS)

all: $(NAME)

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
