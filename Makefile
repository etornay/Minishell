NAME = minishell

MINISHELL = minishell.a

FILES = src/minishell.c\
src/minishell_utils/prompt.c\
src/minishell_utils/split.c\
src/minishell_utils/expand.c\
src/minishell_utils/init_struct.c\
src/minishell_utils/split_token.c\
src/minishell_utils/parser.c\
src/minishell_utils/parser_utils.c\
src/minishell_utils/parser_utils2.c\
src/minishell_utils/heredoc.c\
src/builtins/builtins.c\
src/builtins/builtins2.c\
src/builtins/builtins_utils/builtins_utils.c\
src/builtins/builtins_utils/export_utils.c\
src/builtins/builtins_utils/cd_utils.c\
src/builtins/env_utils/get_path.c\
src/free/free.c\
src/free/free2.c\

OBJECTS = $(FILES:.c=.o)

FLAGS = -Wall -Werror -Wextra -g

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