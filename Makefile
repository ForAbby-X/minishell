# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 09:39:09 by alde-fre          #+#    #+#              #
#    Updated: 2023/06/14 21:12:52 by alde-fre         ###   ########.fr        #
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
			redirs.c \
			command.c\
			\
			parsing/utils.c \
			parsing/error.c \
			parsing/lexer.c \
			parsing/parser.c \

INC		= 	minishell.h \
			token.h \
			redirs.h \
			parsing.h \
			command.h \

OBJ		= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

DEPENDS :=	$(patsubst %.o,%.d,$(OBJ))

# compiler
CC		= cc
CFLAGS	= -MMD -MP -Wall -Wextra -Werror

# vector library
VECTOR		= ./c-vectorlib/
VECTOR_LIB	= $(addprefix $(VECTOR),libvector.a)
VECTOR_INC	= -I $(addprefix $(VECTOR),inc)
VECTOR_LNK	= -l Xext -l X11 -L $(VECTOR) -l libvector -l m

all: obj $(VECTOR_LIB) $(NAME)

raw: CFLAGS += -O0
raw: obj $(VECTOR_LIB) $(NAME)

fast: CFLAGS += -Ofast
fast: obj $(VECTOR_LIB) $(NAME)

debug: CFLAGS += -g3
debug: obj $(VECTOR_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(VECTOR_LIB):
	make -C ./c-vectorlib

$(NAME): $(OBJ)
	@echo "\e[1;35mLinking...\e[0m"
	@$(CC) -o $(NAME) $+ $(VECTOR_LIB) -l readline
	@echo "\e[1;32m➤" $@ "created succesfully !\e[0m"

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "\e[0;36m ↳\e[0;36m" $<"\e[0m"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(VECTOR_INC) -I $(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@make -C $(VECTOR) clean

fclean: clean
	rm -rf $(NAME)
	@make -C $(VECTOR) fclean

re: fclean all

.PHONY: all clean fclean re

-include $(DEPENDS)
