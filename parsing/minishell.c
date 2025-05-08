#include "../minishell.h"

int read_and_filling_node(char *input, t_list **lst) //read_&_filling_node
{
    int i;

    i = 0;
    while (input[i])
    {
        while (input[i] && input[i] != ' ' && input[i] != '\t')
        {
            if (input[i] == '|' || input[i] == '<' || input[i] == '>')
            {
                if (!ft_handel_pipe_direction(input, &i, lst)) // ft_handel_pipe_direction
                    return(0);
            }
            else if (input[i] == '\"' || input[i] == '\'')
            {
                if (!ft_handle_double_single(input, &i, lst))
                    return(0);
            }
            else
            {
                if (!ft_handle_string(input, &i, lst))
                    return(0);
            }
        }
        if (input[i] == ' ' || input[i] == '\t')
            i++;
    }
    return(1);
}

int syntax_erorr(t_list *lst)
{
    if(lst->content[0] == '|' || (((lst->content[0] == '<' || lst->content[0] == '>')
        && (lst->next == NULL))) || ((lst->content[0] == '<' || lst->content[0] == '>')
        && (lst->next->content[0] == '|' || lst->next->content[0] == '<' || lst->next->content[0] == '>')))
    {
        printf("bash: syntax error near unexpected token `%c'\n",lst->content[0]);
        return(0);
    }
    else
    {
        while(lst->next)
        {
            if((lst->content[0] == '<' || lst->content[0] == '>')
                && (lst->next->content[0] == '|' || lst->next->content[0] == '<' || lst->next->content[0] == '>'))
                return(printf("bash: syntax error near unexpected token `%s'\n", lst->next->content), 0);
            else if((lst->content[0] == '|') && (lst->next->content[0] == '|'))
                return(printf("bash: syntax error near unexpected token `|'\n"), 0);
            lst = lst->next;
            if (lst->next == NULL && (lst->content[0] == '|' || lst->content[0] == '<' || lst->content[0] == '>'))
                return(printf("bash: syntax error near unexpected token `newline'\n"), 0);
        }
    }
    return(1);
}


t_node *typed_nodes(t_list *lst) 
{
    t_node  *arg;
    arg = NULL;
    while(lst)
    {
        if(lst->content[0] == '<' || lst->content[0] == '>')
        {
            if(lst->content[0] == '<' && lst->content[1] == '\0')
                ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content,1));
            else if(lst->content[0] == '>' && lst->content[1] == '\0')
                ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content,2));
            else if(lst->content[0] == '<' && lst->content[1] == '<')
                ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content,3));
            else if(lst->content[0] == '>' && lst->content[1] == '>')
                ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content,4));
            lst = lst->next;
        }
        else if(lst->content[0] == '|')
            ft_lstadd_back1(&arg, ft_lstnew1(lst->content,5));
        else
            ft_lstadd_back1(&arg, ft_lstnew1(lst->content,0));
        lst = lst->next;
    }
    return(arg);
}

void expand_variables(t_node *lst, t_env *my_env)
{
    int i;
    int a;
    int j;
    int t;

    i = 0;
    a = 0;
    j = 0;
    t = 0;
    while(lst)
    {
        i = 0;
        if(lst->data[i])
        {
            a = 0;
            while(lst->data[i])
            {
                if(lst->data[i] == '\'' && t % 2 == 0)
                    j++;
                else if(lst->data[i] == '\"' && j % 2 == 0)
                    t++;
                if(lst->data[i] == '$' && (j % 2 == 0))
                    a++;
                i++;
            }
            if(a > 0)
                expanding_function(lst, my_env);
        }
        lst = lst->next;
    }
}

void delete_qoutation(t_node *arg)
{
    int i;
    int j;
    int m;
    int t;
    char *str;
    t_node *tmp = arg;

    while(arg)
    {
        j = 0;
        t = 0;
        i = 0;
        m = 0;
        while(arg->data[i])
        {
            if(arg->data[i] == '\'' && t % 2 == 0)
                j++;
            else if(arg->data[i] == '\"' && j % 2 == 0)
                t++;
            else if((arg->data[i] != '\"' && j % 2 == 0) || (arg->data[i] != '\'' && t % 2 == 0)
                ||(arg->data[i] == '\'' && t % 2 == 1)||(arg->data[i] == '\"' && j % 2 == 1))
            {
                m++;
            }
            i++;
        }
        str = malloc(sizeof(char) * (m + 1));
        i = 0;
        m = 0;
        j = 0;
        t = 0;
        while(arg->data[i])
        {
            if(arg->data[i] == '\'' && t % 2 == 0)
                j++;
            else if(arg->data[i] == '\"' && j % 2 == 0)
                t++;
            else if((arg->data[i] != '\"' && j % 2 == 0) || (arg->data[i] != '\'' && t % 2 == 0)
                ||(arg->data[i] == '\'' && t % 2 == 1)||(arg->data[i] == '\"' && j % 2 == 1))
                str[m++] = arg->data[i];
            i++;
        }
        str[m] = '\0';
        // free(arg->data);
        arg->data = str;
        arg = arg->next;
    }
    while (tmp)
    {
        printf("Toooo: [%s]------>{%d}\n", tmp->data,tmp->type);
        tmp = tmp->next;
    }
}

void exec_commands(t_node **nodes, t_env **my_env)
{
	char *cmd_path;
	char **cmd;

	cmd_path = NULL;
	cmd = NULL;	
	if (piping_forking(cmd_path, cmd, nodes, my_env) == -1)
	{
		perror("Minishell");
		exit(1);
	}
	return ;	
}

int main(int argc, char **argv, char **envp)
{
    // static int num_err;
    t_list *lst;
    t_node *arg;
    t_env *my_envp;
    char *input;

    lst = NULL;
    arg = NULL;
    input = NULL;
    my_envp = NULL;
    while (1)
    {
        lst = NULL;
        input = readline("minishell> ");
        if (!input)
            exit(0);
        if (input[0] == '\0')
        {
            continue;
        }
        add_history(input);
        if (read_and_filling_node(input,&lst))
        {
            if (lst == NULL)
                continue;
            if (syntax_erorr(lst))
            {
                arg = typed_nodes(lst);
                if (!my_envp)
					claiming_env(envp, &my_envp);
                expand_variables(arg, my_envp);
                delete_qoutation(arg);
                // exec_commands(&arg, &my_envp);
                ft_free(&lst);
                ft_free1(&arg);
                // ft_free(&my_envp);
            }
            // else
            //     ft_free(&lst);
        }
        // else
        //     ft_free(&lst);
    }
    return (0);
}
