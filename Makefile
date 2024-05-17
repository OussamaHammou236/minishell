NAME= minishell
CC= cc
CFLAGS= -fsanitize=address
OBJ= pars/pars.c pars/set_spase.c pars/tockention.c libft/ft_split.c libft/ft_substr.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strlcat.c \
libft/ft_strlcpy.c libft/ft_strjoin.c libft/ft_lstadd_back.c libft/ft_lstlast.c libft/ft_lstnew.c pars/ft_mini_split.c \
cd.c cmd.c echo.c env.c exit.c export.c free_memory.c    helper.c main.c parsing_part1.c  parsing_part2.c  pipe_time.c pwd.c unset.c 
OBJ_O= $(OBJ:.c=.o)

all: $(OBJ_O)
	$(CC) $(CFLAGS) $(OBJ_O)  -lreadline -o $(NAME)
	rm -rf $(OBJ_O)

clean:
	rm -rf $(OBJ_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY= clean%