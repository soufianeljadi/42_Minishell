# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 23:52:42 by sdiouane          #+#    #+#              #
#    Updated: 2024/03/26 01:14:06 by sel-jadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc #-g -fsanitize=address 
CFLAGS = -Wall -Wextra -Werror 
RDFLAGS =  -L $(shell brew --prefix readline)/lib -lreadline
SRC = minishell.c \
      parsing/ft_split.c \
	  parsing/lsts.c \
	  parsing/token.c \
	  parsing/parsing.c \
	  parsing/ft_strtock.c \
	  parsing/split_args.c \
	  parsing/add_sep.c \
	  parsing/parse_pipe.c \
	  parsing/parse_redirection.c \
	  parsing/ft_strchr.c \
	  parsing/ft_substr.c \
	  parsing/ft_strlen.c \
	  builtins/builtins.c \
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
