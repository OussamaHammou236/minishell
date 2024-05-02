
NAME= minishell
CC= cc
#CFLAGS= -Wall -Wextra -Werror
OBJ= pars/pars.c libft/ft_split.c libft/ft_substr.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strjoin.c libft/ft_lstadd_back.c libft/ft_lstlast.c libft/ft_lstnew.c pars/ft_mini_split.c
OBJ_O= $(OBJ:.c=.o)

all: $(OBJ_O)
	$(CC) $(CFLAGS) $(OBJ_O) -o $(NAME) -lreadline
	rm -rf $(OBJ_O)

clean:
	rm -rf $(OBJ_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY= clean