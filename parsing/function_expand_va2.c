#include "minishell.h"

void ft_copy(char *dap, char *str, int *a)
{
    int i;

    i = 0;
    while(str[i])
    {
        dap[*a] = str[i];
        i++;
        (*a)++;
    }
}

void ft_copy55(char *str, int *a)
{
    int i;

    i = 0;
    while(str[i])
    {
        i++;
        (*a)++;
    }
}
char *ft_strlen_key(int *i,char *str)
{
    int a;
    int j;
    int len_key;
    char *src;
    len_key = 0;
    a = *i;
    j = 0;
    while((str[a] >= 97 && str[a] <= 122) 
        || (str[a] >= 65 && str[a] <= 90) || (str[a] == 95) || (str[a] >= 48 && str[a] <= 57))
    {
        len_key++;
        if(str[a - 1] == '$' && str[a] >= 48 && str[a] <= 57)
            break;
        a++;
    }
    src = malloc(sizeof(char) * (len_key + 1));
    while((str[*i] >= 97 && str[*i] <= 122) 
        || (str[*i] >= 65 && str[*i] <= 90) || (str[*i] == 95) || (str[*i] >= 48 && str[*i] <= 57))
    {
        src[j++] = str[(*i)++];
        if(str[*i-1] >= 48 && str[*i-1] <= 57 && str[*i - 2] == '$')
            break ;
    }
    src[j] = '\0';
    return (src);
}

void ft_exp55(t_node *lst, t_env *my_env,int *i, int *a)
{
    int b;
    char *src;

    (*i)++;
    if((lst->data[*i] >= 97 && lst->data[*i] <= 122) 
        || (lst->data[*i] >= 65 && lst->data[*i] <= 90) || (lst->data[*i] == 95)|| (lst->data[*i] >= 48 && lst->data[*i] <= 57))
    {
        src = ft_strlen_key(i,lst->data);
    }
    while(my_env)
    {
        b = 0;
        while(my_env->key[b])
        {
            if(my_env->key[b] != src[b])
                break;
            b++;
        }
        if(my_env->key[b] || src[b])
            my_env = my_env->next;
        else
        {
            ft_copy55(my_env->value, a);
            break ;
        }
    }
}
