cc = cc
CFLAGS = -Wall 
NAME = minishell
HEADER = minishell.h 
READ_LINE = -lreadline
SRC = parsing/ft_function_type.c parsing/ftunctoin_ft_fun.c parsing/function1.c  parsing/func_c.c parsing/function_expand_va.c parsing/function_expand_va2.c parsing/function_free.c parsing/function_ft_ha_do_si.c parsing/minishell.c \
	execution/cmd_working.c execution/lst_functions.c execution/utils_func.c execution/fetching.c execution/utils_func2.c execution/utils_func3.c \
	execution/main_work_of_exec.c execution/implementing_types.c execution/get_next_line.c execution/get_next_line_utils.c \

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

