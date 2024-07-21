# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 23:52:42 by sdiouane          #+#    #+#              #
#    Updated: 2024/07/20 12:03:09 by sdiouane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -Wall -Wextra -Werror

RDFLAGS =  -L $(shell brew --prefix readline)/lib -lreadline
SRC =	minishell.c \
		here_doc/here_doc.c \
		here_doc/here_doc_utils.c \
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
		parsing/split_args_helper_two.c \
		parsing/noued_cmd.c \
		parsing/print_export.c \
		parsing/ft_strjoin.c \
		parsing/split_args_helper.c \
		builtins/builtins.c \
		builtins/builtins_utils.c \
		builtins/export.c \
		builtins/export_null.c \
		builtins/export_null_utils.c \
		builtins/export_not_null.c \
		builtins/export_not_null_utils_one.c \
		builtins/export_not_null_utils_two.c \
		builtins/export_not_null_utils_three.c \
		builtins/pwd.c \
		builtins/cd.c \
		builtins/cd_utils.c \
		builtins/unset.c \
		builtins/unset_utils.c \
		builtins/echo.c \
		builtins/exit_fct.c \
    	signals/signal.c \
		execution/find_path.c \
		execution/execution.c \
		execution/check_builtin.c \
		execution/redirections.c \
		execution/redirections_utils.c \
		execution/redirections_utils_two.c \
		execution/redirections_builtins.c \
		execution/redirections_utils_builtins.c \
		execution/redirections_utils_two_builtins.c \
		execution/file_nc.c \
		execution/helper.c \
		execution/helper_two.c \
		execution/split_space_tab.c \
		execution/execution_utils_one.c \
		execution/execution_utils_two.c \
		execution/execution_utils_three.c \
		execution/execution_utils_four.c \
		execution/handle_quotes.c \
		execution/struct2char.c \
		expanding/expanding.c \
		expanding/expanding_utils_one.c \
		expanding/expanding_utils_two.c \
		expanding/expanding_utils_three.c \
		ft_malloc/ft_malloc.c 

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(RDFLAGS)

all: $(NAME)

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
