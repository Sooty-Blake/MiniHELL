/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_interactive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrichard <wrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:51:52 by wrichard          #+#    #+#             */
/*   Updated: 2023/10/20 16:35:24 by wrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if ((getcwd) != NULL)
	{
		dirname = strrchr(cwd, '/');
		if (dirname != NULL)
			printf("%s ", dirname + 1);
	}
	printf("%s /ᐠ｡ꞈ｡ᐟ\\ %s", getenv("USER"), DEFAULT);
}

void	ft_shell_interactive(void)
{
	char	*line;
	char	**args;
	int		status;

	while (1)
	{
		ft_prompt();
		line = readline("");
		if (!strcmp(line, "exit"))
		{
			return ;
		}
	}
	return ;
}
