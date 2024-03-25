# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 23:52:42 by sdiouane          #+#    #+#              #
#    Updated: 2024/03/25 16:58:31 by sdiouane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g -fsanitize=address 
CFLAGS = -Wall -Wextra -Werror 
RDFLAGS =  -L $(shell brew --prefix readline)/lib -lreadline
SRC = main.c \
      parsing/ft_split.c \
	  parsing/lsts.c \
	  parsing/token.c \
	  parsing/parsing.c \
	  parsing/ft_strtock.c \
	  parsing/parse_pipe.c \
	  parsing/parse_redirection.c \
	  parsing/ft_strchr.c \
	  parsing/ft_substr.c \
	  builtins/export.c \
	  builtins/pwd.c \
	  builtins/cd.c \
	  builtins/unset.c \
	  builtins/echo.c \
      signals/signal.c \

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
