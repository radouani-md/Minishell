#include "../minishell.h"

int ft_fun(char *input,t_list **lst)
{
    int i;

    i = 0;
    while (input[i])
    {
        while (input[i] && input[i] != ' ' && input[i] != '\t')
        {
            if (input[i] == '|' || input[i] == '<' || input[i] == '>')
            {
                if (!ft_pips(input, &i, lst))
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

int ft_syntax_erorr(t_list *lst)
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


t_node *ft_type_comente_in_out_put(t_list *lst) 
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

void ft_expand_variables(t_node *lst, t_env *my_env)
{
    int i;
    int a;
    int j;
    int t;

    i = 0;
    a = 0;
    j = 0;
    t = 0;
    // t_node *tmp = lst;
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
                ft_exp(lst, my_env);
        }
        lst = lst->next;
    }
}

void ft_dapel_qotichin(t_node *lst)
{
    int i;
    int j;
    int m;
    int t;
    char *str;
    t_node *tmp = lst;

    while(lst)
    {
        j = 0;
        t = 0;
        i = 0;
        m = 0;
        while(lst->data[i])
        {
            if(lst->data[i] == '\'' && t % 2 == 0)
                j++;
            else if(lst->data[i] == '\"' && j % 2 == 0)
                t++;
            else if((lst->data[i] != '\"' && j % 2 == 0) || (lst->data[i] != '\'' && t % 2 == 0)
                ||(lst->data[i] == '\'' && t % 2 == 1)||(lst->data[i] == '\"' && j % 2 == 1))
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
        while(lst->data[i])
        {
            if(lst->data[i] == '\'' && t % 2 == 0)
                j++;
            else if(lst->data[i] == '\"' && j % 2 == 0)
                t++;
            else if((lst->data[i] != '\"' && j % 2 == 0) || (lst->data[i] != '\'' && t % 2 == 0)
                ||(lst->data[i] == '\'' && t % 2 == 1)||(lst->data[i] == '\"' && j % 2 == 1))
                str[m++] = lst->data[i];
            i++;
        }
        str[m] = '\0';
        //free(lst->data);
        lst->data = str;
        str = NULL;
        lst = lst->next;
    }
    while (tmp)
    {
        printf("Toooo: [%s]--->%d\n", tmp->data, tmp->type);
        tmp = tmp->next;
    }
}

void print_node(t_env *my_env)
{
	while (my_env)
	{
		printf("{%s} = {%s}\n", my_env->key, my_env->value);
		my_env = my_env->next;
	}
}

int main(int argc, char **argv, char **envp)
{
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
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        add_history(input);
        if(ft_fun(input,&lst))
        {
            if(lst == NULL)
                continue;
            if(ft_syntax_erorr(lst))
            {
                arg = ft_type_comente_in_out_put(lst);
                claiming_env(envp, &my_envp);
                ft_expand_variables(arg, my_envp);
                ft_dapel_qotichin(arg);
            }
        }
    } 
    return (free(input),ft_free(&lst),0);
}
