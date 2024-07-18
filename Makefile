NAME= minishell
CC= cc
#CFLAGS= -Wall -Wextra -Werror
#CFLAGS= -fsanitize=address -g3
OBJ= pars/pars.c pars/set_spase.c pars/expand.c pars/tockention.c pars/check_str.c  pars/check_herdoc.c libft/ft_strncmp.c pars/free_trash.c pars/expand_2.c\
libft/ft_split.c libft/ft_substr.c libft/ft_itoa.c libft/ft_bzero.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strlcat.c \
libft/ft_strlcpy.c libft/ft_strjoin.c libft/ft_lstadd_back.c libft/ft_lstlast.c libft/ft_lstnew.c pars/ft_mini_split.c  libft/ft_atoi.c \
execution/files_cd/cd.c execution/files_cd/helper_cd.c execution/cmd.c execution/echo.c execution/env.c execution/exit.c execution/files_export/export.c execution/free_memory.c\
execution/files_export/export_part_two.c execution/files_export/export_part_three.c execution/files_export/export_part_four.c \
execution/helper_func/helper.c execution/helper_func/helper_part_one.c execution/helper_func/helper_part_two.c execution/main.c execution/parsing_part1.c   \
execution/files_pipe_time/pipe_time.c execution/files_pipe_time/helper_pipe.c execution/pwd.c execution/files_unset/unset.c execution/files_unset/delete_var.c \
execution/files_herdoc/herdoc.c execution/files_herdoc/rediriction.c execution/signals.c

OBJ_O= $(OBJ:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_O)
	$(CC)  $(OBJ_O) $(CFLAGS) -lreadline -o $(NAME)


clean:
	rm -rf $(OBJ_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean

.SECONDARY: $(OBJ_O)