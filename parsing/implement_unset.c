#include "../minishell.h"

void delete_node(t_env **env_node)
{
    t_env *temp;

    if (env_node == NULL || *env_node == NULL)
        return;

    temp = *env_node;
    *env_node = (*env_node)->next;
    free(temp->key);
    free(temp->value);
    free(temp);
}

int	implement_unset(t_env **my_env, t_node *nodes)
{
    t_env	**cpy_env;
    int i;

    nodes = nodes->next;
    while(nodes)
    {
        i = 0;
        cpy_env = my_env;
        while (*cpy_env)
        {
            if (!ft_strcmp((*cpy_env)->key, ft_cpy_key(i, nodes)))
			{
				delete_node(cpy_env);
				break ;
			}
            *cpy_env = (*cpy_env)->next;
        }
        nodes = nodes->next;
    }
    return (0);
}
