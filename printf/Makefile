CC=cc
CFLAGS= -Wall -Wextra -Werror
NAME=libftprintf.a
UTILS_DIR=utils
PRINTERS_DIR=printers
PRINTERS_SRCS=ft_printf_chr.c  ft_printf_hex.c  ft_printf_percent.c  ft_printf_ptr.c  ft_printf_str.c ft_printf_int.c ft_printf_u_int.c
UTILS_SRCS=ft_putchar.c  ft_putnbr_base.c  ft_putstr.c  ft_u_putnbr_base.c
PRINTERS_SRCS_PATHS = $(addprefix $(PRINTERS_DIR)/, $(PRINTERS_SRCS))
UTILS_SRCS_PATHS = $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))

SRCS=ft_printf.c $(PRINTERS_SRCS_PATHS) $(UTILS_SRCS_PATHS)
OBJS= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	@echo "Completed"

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
