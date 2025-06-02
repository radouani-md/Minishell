CC = cc
CFLAGS = -Wall -fsanitize=address -g
NAME = minishell 
HEADER = minishell.h 
READ_LINE = -lreadline

SRC = parsing/gc_malloc.c parsing/implement_unset.c parsing/minishell.c parsing/implement_export.c parsing/ft_read_and_filling_node.c parsing/ft_1read_and_filling_node.c parsing/ft_syntax_erorr.c parsing/ft_typed_nodes.c parsing/ft_claiming_env.c \
	parsing/ft_expand_variables.c parsing/ft_1expand_variables.c parsing/ft_2expand_variables.c parsing/ft_delete_qoutation.c parsing/count_handle_str.c\
	utils_function/utils_func.c utils_function/utils_func2.c utils_function/utils_func3.c utils_function/utils_func4.c \
	utils_function/yl_utils_func.c utils_function/yl_utils_func2.c utils_function/yl_utils_func3.c utils_function/yl_utils_func4.c \
	execution/cmd_working.c execution/lst_functions.c execution/fetching.c execution/main_work_of_exec.c execution/implementing_types.c execution/get_next_line.c \
	execution/get_next_line_utils.c execution/expand_dollar_heredoc.c execution/implement_types_2.c execution/built_in.c execution/built_in2.c \

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) $(READ_LINE) -o $@

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

