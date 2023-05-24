# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 09:39:09 by alde-fre          #+#    #+#              #
#    Updated: 2023/05/23 20:22:48 by alde-fre         ###   ########.fr        #
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
			\
			parsing/word.c \

INC		= 	minishell.h \
			token.h \
			parsing.h \

OBJ		= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

DEPENDS :=	$(patsubst %.o,%.d,$(OBJ))
-include $(DEPENDS)

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
	@rm -rf .print
	@mkdir -p $(OBJDIR)

$(VECTOR_LIB):
	make -C ./c-vectorlib

.print:
	@> $@
	@echo "\e[1;36mCompiling...\e[0m"

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
