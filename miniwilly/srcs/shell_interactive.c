/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_interactive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrichard <wrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:51:52 by wrichard          #+#    #+#             */
/*   Updated: 2023/12/01 18:29:41 by wrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_child_execute(pid_t pid, char **args)
{
	if (execvp(args[0], args) == -1)
	{
		exit(EXIT_FAILURE);
	}
}

int ft_execute(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		ft_child_execute(pid, args);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			ft_error("waitpid");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_arg_handler(char **args)
{
	if (args[0] == NULL)
	{
		return (1);
	}
	return (ft_execute(args));
}

void	ft_prompt(void)
{
	char	cwd[1024];
	char	*dirname;
	char	hostname[256];
	int		i;

	i = 0;
	printf("%s", CYAN);
	gethostname(hostname, sizeof(hostname));
	while (hostname[i] != '.')
	{
		if (hostname[i] == '\0')
			break ;
		printf("%c", hostname[i]);
		i++;
	}
	printf(":");
	getcwd(cwd, sizeof(cwd) - 1);
	if (getcwd(cwd, sizeof(cwd) - 1) != NULL)
	{
		dirname = strrchr(cwd, '/');
		if (dirname != NULL)
			printf("%s ", dirname + 1);
	}
	printf("%s ฅ^•ﻌ•^ฅ %s", getenv("USER"), DEFAULT);
}

void	ft_shell_interactive(void)
{
	char	*line;
	char	**args;
	int		i;

	while (1)
	{
		ft_prompt();
		line = readline("");
		if (line == NULL)
		{
			printf("%sExiting ฅ^-_-^ฅ%s\n", RED, DEFAULT);
			return ;
		}
		args = ft_split(line, ' ');
		i = 0;
		while (args[i])
		{
			printf("%s\n", args[i]);
			i++;
		}
		ft_arg_handler(args);
		free(line);
		free(args);
	}
	return ;
}
