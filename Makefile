NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_printf.c ft_print_char.c ft_print_str.c \
       ft_print_ptr.c ft_print_nbr.c ft_print_unsigned.c ft_print_hex.c \
       ft_print_utils.c

BONUS_SRCS = ft_printf_bonus.c ft_parse_format_bonus.c ft_print_char_bonus.c \
             ft_print_str_bonus.c ft_print_ptr_bonus.c ft_print_nbr_bonus.c \
             ft_print_unsigned_bonus.c ft_print_hex_bonus.c ft_print_utils_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

bonus: $(LIBFT) $(BONUS_OBJS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(BONUS_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
