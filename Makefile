# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 06:04:10 by sdiouane          #+#    #+#              #
#    Updated: 2024/06/10 06:04:13 by sdiouane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = cc -g -fsanitize=address


RDFLAGS =  -L $(shell brew --prefix readline)/lib -lreadline

SRC =	minishell.c \
		here_doc/here_doc.c \
		parsing/exit_stat.c \
		parsing/ft_itoa.c \
		parsing/promt.c \
    	parsing/ft_split.c \
		parsing/lsts.c \
		parsing/parsing.c \
		parsing/ft_strtock.c \
		parsing/split_args.c \
		parsing/split_by_pipe.c \
		parsing/add_sep.c \
		parsing/parse_pipe.c \
		parsing/parse_redirection.c \
		parsing/ft_strchr.c \
		parsing/quotes.c \
		parsing/ft_substr.c \
		parsing/ft_strlen.c \
		parsing/split_args_helper.c \
		builtins/builtins.c \
		builtins/export.c \
		builtins/export_null.c \
		builtins/export_not_null.c \
		builtins/export_not_null_utils.c \
		builtins/pwd.c \
		builtins/cd.c \
		builtins/unset.c \
		builtins/echo.c \
		builtins/exit_fct.c \
    	signals/signal.c \
		execution/find_path.c \
		execution/execution.c \
		execution/redirections.c \
		execution/helper.c \
		execution/split_space_tab.c \
		execution/heredoc.c \
		execution/execution_utils.c \
		execution/merge_env.c  \
		execution/handle_quotes.c \
		expanding/expanding.c \
		expanding/expanding_utils.c \
		allocate/ft_allocate.c 

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L $(shell brew --prefix readline)/lib -lreadline

all: $(NAME)

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
