NAME= minishell
CC= cc
#CFLAGS= -Wall -Wextra -Werror
#CFLAGS= -fsanitize=address -g3
OBJ= pars/pars.c pars/set_spase.c pars/expand.c pars/tockention.c libft/ft_strncmp.c pars/free_trash.c pars/expand_2.c\
libft/ft_split.c libft/ft_substr.c libft/ft_itoa.c libft/ft_bzero.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strlcat.c \
libft/ft_strlcpy.c libft/ft_strjoin.c libft/ft_lstadd_back.c libft/ft_lstlast.c libft/ft_lstnew.c pars/ft_mini_split.c  libft/ft_atoi.c \
execution/cd.c execution/cmd.c execution/echo.c execution/env.c execution/exit.c execution/export.c execution/free_memory.c\
execution/helper.c execution/main.c execution/parsing_part1.c  execution/parsing_part2.c \
execution/pipe_time.c execution/pwd.c execution/unset.c \
execution/herdoc.c execution/signals.c

OBJ_O= $(OBJ:.c=.o)

all: $(OBJ_O)
	$(CC) $(CFLAGS) $(OBJ_O)  -lreadline -o $(NAME)
	rm -rf $(OBJ_O)

clean:
	rm -rf $(OBJ_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all

push: fclean
	@git add .
	@git commit -m "beta_v"
	@git push

.PHONY= clean