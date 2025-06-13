CC = cc
CFLAGS = -Wall #-Wextra -Werror #-fsanitize=address -g
NAME = minishell 
HEADER = minishell.h 
READ_LINE = -lreadline

SRC = parsing/cc.c parsing/gc_malloc.c parsing/implement_unset.c parsing/minishell.c parsing/implement_export.c parsing/ft_read_and_filling_node.c parsing/ft_1read_and_filling_node.c parsing/ft_syntax_erorr.c parsing/ft_typed_nodes.c parsing/ft_claiming_env.c \
	parsing/ft_expand_variables.c parsing/ft_1expand_variables.c parsing/ft_2expand_variables.c parsing/ft_delete_qoutation.c parsing/count_handle_str.c\
	utils_function/utils_func.c utils_function/utils_func2.c utils_function/utils_func3.c utils_function/utils_func4.c \
	utils_function/yl_utils_func.c utils_function/yl_utils_func2.c utils_function/yl_utils_func3.c utils_function/yl_utils_func4.c \
	utils_function/yl_utils_func5.c utils_function/yl_utils_func6.c\
	execution/cmd_working.c execution/lst_functions.c execution/fetching.c execution/main_work_of_exec.c execution/implementing_types.c \
	execution/expand_dollar_heredoc.c execution/implement_types_2.c execution/built_in.c execution/built_in2.c execution/get_next_line_utils.c \
	execution/parent_child_pro.c \
	execution/built_in_cd.c execution/built_in_cd2.c execution/cmd_working2.c execution/implement_types_2_2.c execution/main_work_of_exec2.c execution/handel_signals.c \
	my_printf/ft_printf.c my_printf/ft_utils.c my_printf/ft_putnum.c my_printf/ft_puthex.c my_printf/ft_putpoint.c my_printf/ft_printmix.c \

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

