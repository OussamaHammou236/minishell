CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME := libft.a
part1 = ft_atoi.c ft_bzero.c  ft_calloc.c ft_isalnum.c  ft_isalpha.c  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcpy.c ft_memmove.c \
		ft_memset.c ft_memcmp.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c 
part1_o = ft_atoi.o ft_bzero.o  ft_calloc.o ft_isalnum.o  ft_isalpha.o  ft_isascii.o ft_isdigit.o ft_isprint.o ft_itoa.o ft_memchr.o ft_memcpy.o ft_memmove.o \
		 ft_memset.o ft_memcmp.o ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o ft_split.o ft_strchr.o ft_strdup.o ft_striteri.o ft_strjoin.o ft_strlcat.o ft_strlcpy.o ft_strlen.o \
		 ft_strmapi.o ft_strncmp.o ft_strnstr.o ft_strrchr.o ft_strtrim.o ft_substr.o ft_tolower.o ft_toupper.o 
bonus_part = ft_lstnew_bonus.c  ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c 
bonus_part_o = ft_lstnew_bonus.o  ft_lstsize_bonus.o ft_lstlast_bonus.o ft_lstadd_back_bonus.o

all: $(NAME)

$(NAME): $(part1_o)
	ar rcs $(NAME) $(part1_o)

$(part1_o) :
	$(CC) $(CFLAGS) -c $(part1)

$(bonus_part_o) : $(bonus_part)
	$(CC) $(CFLAGS) -c $(bonus_part) 
	ar rcs $(NAME) $(bonus_part_o)
bonus: $(bonus_part_o)
	

clean:
	rm -f $(part1_o) $(bonus_part_o)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus re fclean clean
