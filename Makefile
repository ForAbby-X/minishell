# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 09:39:09 by alde-fre          #+#    #+#              #
#    Updated: 2023/07/17 16:18:52 by alde-fre         ###   ########.fr        #
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
			word.c \
			parsing/utils.c \
			parsing/error.c \
			parsing/lexer.c \
			parsing/expand_exceptions.c \
			parsing/expand.c \
			parsing/parser.c \
			parsing/merge_tokens.c \
			parsing/merge_redirs.c \
			parsing/split_to_commands.c \
			env/env_utils.c \
			env/env_create.c \
			env/env_destroy.c \
			env/env_shlvl.c \
			exec/path/get_command_path.c \
			exec/path/path_utils.c \
			exec/exec/ft_execvpe.c \
			exec/exec/args.c \
			exec/core/run_command.c \
			exec/core/spawn_commands.c \
			exec/core/interface.c \
			exec/redirs/redirs.c \
			exec/heredoc/heredoc_file.c \
			exec/heredoc/heredoc_utils.c \
			exec/heredoc/heredoc.c \
			exec/heredoc/heredoc_expand.c \
			utils/string.c \
			utils/numbers.c \
			signals/signals.c \
			signals/handlers.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/cd.c \
			builtins/pwd.c \
			builtins/env.c \
			builtins/unset.c \
			builtins/export/core.c \
			builtins/export/display.c \
			builtins/empty.c \
			builtins/builtins.c \
			exec/exec/builtins_exec.c

INC		= 	minishell.h \
			token.h \
			word.h \
			redirs.h \
			parsing.h \
			env.h \
			command.h \

OBJ		= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

DEPENDS :=	$(patsubst %.o,%.d,$(OBJ))

# compiler
CC		= cc
CFLAGS	= -MMD -MP -Wall -Wextra -g3 -Werror

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

# libft library
FT_PRINTF		= ./printf/
FT_PRINTF_LIB	= $(addprefix $(FT_PRINTF),libftprintf.a)
FT_PRINTF_INC	= -I $(FT_PRINTF)
FT_PRINTF_LNK	= -l Xext -l X11 -L $(FT_PRINTF) -l libftprintf -l m

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

$(FT_PRINTF_LIB):
	make -C $(FT_PRINTF)

.print:
	@> $@
	@echo "\e[1;36mCompiling...\e[0m"

$(NAME): $(OBJ) $(VECTOR_LIB) $(LIBFT_LIB) $(FT_PRINTF_LIB)
	@echo "\e[1;35mLinking...\e[0m"
	@$(CC) -o $(NAME) $+ $(VECTOR_LIB) $(LIBFT_LIB) $(FT_PRINTF_LIB) -l readline
	@echo "\e[1;32m➤" $@ "created succesfully !\e[0m"

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "\e[0;36m ↳\e[0;36m" $<"\e[0m"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(VECTOR_INC) $(LIBFT_INC) $(FT_PRINTF_INC) -I $(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@make -C $(VECTOR) clean
	@make -C $(LIBFT) clean
	@make -C $(FT_PRINTF) clean

fclean: clean
	rm -rf $(NAME)
	@make -C $(VECTOR) fclean
	@make -C $(LIBFT) fclean
	@make -C $(FT_PRINTF) fclean

re: fclean all

-include $(DEPENDS)

.PHONY: all clean fclean re

-include $(DEPENDS)
