#include "../minishell.h"

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
    while(ft_Check_after_dollar(str[a]))
    {
        len_key++;
        if(str[a - 1] == '$' && ((str[a] >= 48 && str[a] <= 57) || str[a] == '?'))
            break;
        a++;
    }
    src = malloc(sizeof(char) * (len_key + 1));
    if(!src)
        return(NULL);
    while(ft_Check_after_dollar(str[*i]))
    {
        src[j++] = str[(*i)++];
        if(((str[*i - 1] >= 48 && str[*i - 1] <= 57) || str[*i - 1] == '?') && str[*i - 2] == '$')
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
    if(ft_Check_after_dollar(lst->data[*i]))
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
    if(src[0] == '?')
        *a = *a + ft_strlen_num_err(); // حساب عدد pid اضافته على a
    free(src);
}
