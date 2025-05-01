#include "../minishell.h"

static int	ft_length(long number)
{
	int	length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		number *= -1;
		length++;
	}
	while (number > 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

static void	ft_fill_string(char *string, long number, int len)
{
	string[len] = '\0';
	if (number == 0x0)
		string[0x0] = '0';
	else
	{
		if (number < 0x0)
		{
			string[0x0] = '-';
			number = -number;
		}
		while (number)
		{
			string[--len] = (number % 0xa) + '0';
			number /= 0xa;
		}
	}
}

char *ft_itoa(int nbr)
{
	int		length;
	long	number;
	char	*string;

	number = nbr;
	length = ft_length(number);
	string = ((char *)malloc(length + 0x1));
	if (!string)
		return (NULL);
	ft_fill_string(string, number, length);
	return (string);
}


int ft_strlen_num_err(void)
{
    int i;
    int num_err;
    char *str;

    i = 0;
    num_err = 127;
    str = ft_itoa(num_err);
    while(str[i])
        i++;
    return(i);
}



void ft_functin_env(char *dap, int *a)
{
    int i;
    i = 0;
    char *str;
    // int num_err = 0;
    str = "0"; // ft_itoa(num_err);
    while(str[i])
    {
        dap[(*a)++] = str[i++];
    }
}
