# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 23:52:42 by sdiouane          #+#    #+#              #
#    Updated: 2024/03/25 15:20:22 by sdiouane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g -fsanitize=address 
CFLAGS = -Wall -Wextra -Werror 
RDFLAGS =  -L $(shell brew --prefix readline)/lib -lreadline
SRC = main.c \
      ft_split.c \
	  lsts.c \
	  token.c \
	  parsing.c \
	  ft_strtock.c \
	  parse_pipe.c \
	  parse_redirection.c \
	  ft_strchr.c \
	  ft_substr.c \
	  export.c \
	  pwd.c \
	  cd.c \
	  unset.c \
	  echo.c \
      signal.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(RDFLAGS)

all: $(NAME)

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
