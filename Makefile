# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 09:39:09 by alde-fre          #+#    #+#              #
#    Updated: 2023/07/04 17:44:50 by olimarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

# directories
SRCDIR	=	./src
INCDIR	=	./inc
OBJDIR	=	./obj

# src / includes / obj files
SRC		=	main.c \
			token.c \
			command.c\
			error.c\
			\
			parsing/utils.c \
			parsing/error.c \
			parsing/lexer.c \
			parsing/expand.c \
			parsing/parser.c \
			parsing/merge_tokens.c \
			parsing/merge_redirs.c \
			parsing/split_to_commands.c \
			env/env_utils.c \
			exec/path/get_command_path.c \
			exec/path/path_utils.c \
			exec/exec/ft_execvpe.c \
			exec/exec/args.c \
			exec/exec/exec_command.c \
			exec/core/run_command.c \
			exec/core/spawn_commands.c \
			exec/core/interface.c \
			exec/redirs/redirs.c \
			exec/heredoc/heredoc_file.c \
			exec/heredoc/heredoc.c \
			utils/string.c \
			signals/signals.c \
			signals/handlers.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/cd.c \
			builtins/pwd.c \
			builtins/env.c \
			builtins/builtins.c \
			exec/exec/builtins_exec.c

INC		= 	minishell.h \
			token.h \
			redirs.h \
			parsing.h \
			env.h \
			command.h \

OBJ		= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

DEPENDS :=	$(patsubst %.o,%.d,$(OBJ))

# compiler
CC		= clang
CFLAGS	= -MMD -MP -Wall -Wextra -g
# -Werror

# vector library
VECTOR		= ./c-vectorlib/
VECTOR_LIB	= $(addprefix $(VECTOR),libvector.a)
VECTOR_INC	= -I $(addprefix $(VECTOR),inc)
VECTOR_LNK	= -L $(VECTOR) -l libvector

# libft library
LIBFT		= ./libft/
LIBFT_LIB	= $(addprefix $(LIBFT),libft.a)
LIBFT_INC	= -I $(LIBFT)
LIBFT_LNK	= -l Xext -l X11 -L $(LIBFT) -l llibft -l m

all: obj $(NAME)

raw: CFLAGS += -O0
raw: obj $(NAME)

fast: CFLAGS += -Ofast
fast: obj $(NAME)

debug: CFLAGS += -g3
debug: obj $(NAME)

obj:
	@mkdir -p $(OBJDIR)


$(VECTOR_LIB):
	make -C ./c-vectorlib


$(LIBFT_LIB):
	make -C $(LIBFT)

.print:
	@> $@
	@echo "\e[1;36mCompiling...\e[0m"

$(NAME): $(OBJ) $(VECTOR_LIB) $(LIBFT_LIB)
	@echo "\e[1;35mLinking...\e[0m"
	@$(CC) -o $(NAME) $+ $(VECTOR_LIB) $(LIBFT_LIB) -l readline
	@echo "\e[1;32m➤" $@ "created succesfully !\e[0m"

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "\e[0;36m ↳\e[0;36m" $<"\e[0m"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(VECTOR_INC) $(LIBFT_INC) -I $(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@make -C $(VECTOR) clean
	@make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	@make -C $(VECTOR) fclean
	@make -C $(LIBFT) fclean

re: fclean all

-include $(DEPENDS)

.PHONY: all clean fclean re

-include $(DEPENDS)
