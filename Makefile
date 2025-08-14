# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: salhali <salhali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 17:02:36 by salhali           #+#    #+#              #
#    Updated: 2025/08/14 17:31:23 by salhali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = #-Wall -Wextra -Werror #-g3 -fsanitize=address
LIBS = -lreadline -lncurses
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = builtins/builtin_echo.c \
      builtins/builtins.c \
      builtins/builtin_cd.c \
      builtins/builtin_env.c \
      builtins/builtin_unset.c \
      builtins/builtin_pwd.c \
      builtins/builtin_export.c \
      builtins/builtin_exit.c \
      builtins/builtin_source.c \
      utils/utils.c \
      utils/signal.c \
      helper.c \
      helper1.c \
      helper2.c \
      execution/execute.c \
      execution/redirections.c \
      execution/path.c \
      execution/filter_cmd.c \
      parser/expand.c \
      parser/fill_array.c \
      parser/free.c \
      parser/helpers.c \
      parser/helpersplus.c \
      parser/initializer.c \
      parser/linked_list.c \
      parser/parsing.c \
      parser/print.c \
      parser/quotes.c \
      tokenizer/build_command_list.c \
      tokenizer/rederiction.c \
      tokenizer/tokenizer.c \
      utils/heredoc_input.c \
      main.c \
      clean_up.c helpew.c parser/expandplus.c parser/helpers1.c parser/init_help.c parser/free_plus.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -no-pie -o $(NAME)

clean :
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY: all clean fclean re
