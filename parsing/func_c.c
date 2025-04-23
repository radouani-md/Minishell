// #include "../minishell.h"

// static int	alloction(int n)
// {
// 	int	i;

// 	i = 0;
// 	if (n == 0)
// 		return (1);
// 	if (n < 0)
// 		i += 1;
// 	while (n != 0)
// 	{
// 		n /= 10;
// 		i++;
// 	}
// 	return (i);
// }

// static void	copyintoarray(long nb, size_t i, char *p)
// {
// 	while (nb > 0)
// 	{
// 		p[--i] = (nb % 10) + '0';
// 		nb /= 10;
// 	}
// }

// char	*ft_itoa(int n)
// {
// 	char	*p;
// 	size_t	i;
// 	long	nb;

// 	i = alloction(n);
// 	nb = n;
// 	p = (char *) malloc(sizeof(char) * (i + 1));
// 	if (!p)
// 		return (0);
// 	p[i] = '\0';
// 	if (n == 0)
// 	{
// 		p[0] = '0';
// 		return (p);
// 	}
// 	if (n < 0)
// 	{
// 		nb = -nb;
// 		p[0] = '-';
// 	}
// 	copyintoarray(nb, i, p);
// 	return (p);
// }


// void ft_functin_$(char *dap,int *a)
// {
//     // int status;
//     // int g_exit_status;
//     char *str;
//     int i = 0;
//     pid_t pid = fork();
// 	if (pid == -1)
// 	{

// 	}
//     else if (pid == 0)
//     {
//         // في العملية الابن
//         // execve(cmd, args, envp);
//         // perror("execve 0 \n"); // لو فشل exec
//         // exit(1);          // اخرج بكود 1
// 		;
// 	}
//     else
//     {
//         // في العملية الأب
//         // waitpid(pid, &status, 0);

//         // if (WIFEXITED(status)) {
//         //     g_exit_status = WEXITSTATUS(status);  // ✅ احفظ كود الخروج هنا
//         // }
//         printf("127\n");
//         // exit(1);
//     }
//     str = ft_itoa(pid);
//     while(str[i])
//     {
//         dap[*a] = str[i];
//         i++;
//     }
// }
