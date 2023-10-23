/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_interactive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qubemap <qubemap@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:51:52 by wrichard          #+#    #+#             */
/*   Updated: 2023/10/23 16:11:17 by qubemap          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lsh_launch(char **args)
{
  pid_t pid;
  pid_t wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int lsh_execute(char **args)
{
  //int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }
/*
  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
*/
  return lsh_launch(args);
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
	//int		status;
	int i;

	while (1)
	{
		ft_prompt();
		line = readline("");
		args = ft_split(line, ' ');
		i = 0;
		while (args[i])
		{
			printf("%s\n", args[i]);
			i++;
		}
		if (line == NULL) /* ctr + d*/
			return ;
		lsh_execute(args);
		free(line);
		free(args);
	}
	return ;
}
