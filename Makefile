NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
LIBFT_PATH	=	libft/
LIBFT 		=	libft/libft.a

OBJ			=	pars/pars.c pars/set_spase.c pars/expand.c pars/check_herdoc.c pars/check_str.c pars/tockention.c pars/free_trash.c pars/expand_2.c \
    			pars/ft_mini_split.c pars/run_true.c pars/ft_status.c \
    			execution/files_cd/cd.c execution/files_cd/helper_cd.c execution/cmd.c execution/echo.c execution/env.c execution/exit.c execution/files_export/export.c execution/free_memory.c \
    			execution/files_export/export_part_two.c execution/files_export/export_part_three.c execution/files_export/export_part_four.c \
    			execution/helper_func/helper.c execution/helper_func/helper_part_one.c execution/helper_func/helper_part_two.c execution/main.c execution/comand/parsing_part1.c \
    			execution/files_pipe_time/pipe_time.c execution/files_pipe_time/helper_pipe.c execution/pwd.c execution/files_unset/unset.c execution/files_unset/delete_var.c \
    			execution/files_herdoc/herdoc.c execution/files_herdoc/rediriction.c execution/signals.c execution/comand/p_part2.c \
				execution/helper_func/helper_part_three.c execution/files_pipe_time/process_first_herdocs.c execution/files_export/display_export.c \
				execution/helper_func/helper_part_four.c execution/comand/parsing_part2.c execution/files_export/export_d.c \
				execution/files_herdoc/helping_red.c execution/files_pipe_time/helper_pipe_part.c execution/files_cd/helper_cd_part.c execution/helper_exit.c \
				execution/helper_exit_part.c execution/malloc_manage.c execution/mainc_part.c

OBJ_O		=	$(OBJ:.c=.o)

all:	$(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)
	make -C $(LIBFT_PATH) bonus

$(NAME): $(LIBFT) $(OBJ_O)
	$(CC) $(OBJ_O) $(LIBFT) $(CFLAGS) -lreadline -o $(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_O)

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: clean fclean re all

.SECONDARY: $(OBJ_O)