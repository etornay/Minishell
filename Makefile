NAME = minishell

MINISHELL = minishell.a

FILES = src/minishell.c\
src/prompt.c\
src/builtins/builtins.c\
src/builtins/builtins2.c\
src/builtins/env_utils/get_path.c\
src/split.c\
src/init_struct.c\
src/builtins/builtins_utils/builtins_utils.c\
src/builtins/builtins_utils/export_utils.c\
src/builtins/builtins_utils/cd_utils.c\
src/free.c\
src/free_2.c\

OBJECTS = $(FILES:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIBFT = ./Libft/libft.a

LIB_SYS = -Iinclude -lreadline -L "/Users/etornay-/.brew/opt/readline/include"

$(NAME):			$(OBJECTS) $(LIBFT)
						@ ar rcs $(MINISHELL) $(OBJECTS)
						@ gcc $(FLAGS) $(MINISHELL) $(LIBFT) $(LIB_SYS) -o $(NAME) -lreadline

$(OBJECTS):			src/%.o : src/%.c
						@ gcc $(FLAGS) -c $< -o $@

$(LIBFT):
					@ make -s -C ./Libft

all:				$(NAME)

clean:
					@ rm -f $(OBJECTS)
					@ make clean -s -C ./Libft

fclean:
					@ rm -f $(NAME) $(OBJECTS) $(MINISHELL) $(LIBFT)
					@ make fclean -s -C ./Libft

re:					fclean all

.PHONY: all re clean fclean