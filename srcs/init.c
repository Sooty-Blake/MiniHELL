/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:28:25 by bburston          #+#    #+#             */
/*   Updated: 2023/10/05 13:28:30 by bburston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_program(t_program *program, char **envp)
{
	int	i;

	i = 0;
	program->token = (char **)malloc((MAXLIST + 1) * sizeof(char *));
	while (i < MAXLIST + 1)
	{
		program->token[i] = NULL;
		i++;
	}
	program->envar = split_env_var(envp);
	init_envp_first_run(program, envp);
	program->token[i] = NULL;
	init_env_vars(program);
}

t_envar	*init_env(char *name, char *value)
{
	t_envar	*new;

	new = malloc(sizeof(t_envar));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	init_env_vars(t_program *program)
{
	char	cwd[256];
	t_envar	*pwd;
	t_envar	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("Failed to get current directory\n");
		ft_free(program);
		ft_exit(1);
	}
	pwd = init_env("PWD", cwd);
	oldpwd = init_env("OLDPWD", cwd);
	add_env_var(pwd, program);
	add_env_var(oldpwd, program);
	free(pwd->name);
	free(pwd->value);
	free(pwd);
	free(oldpwd->name);
	free(oldpwd->value);
	free(oldpwd);
}

static char	*get_user_prompt(void)
{
	char	*prompt;
	char	*username;
	char	*temp;
	char	*temp_2;

	prompt = getenv("PWD");
	username = getenv("USER");
	if (username)
	{
		temp = ft_strjoin(prompt, " || ");
		temp_2 = ft_strjoin(temp, username);
		prompt = ft_strjoin(temp_2, " || minishell$ ");
		free(temp);
	}
	else
		printf("username does not exist\n");
	return (prompt);
}

int	take_input(char *input, t_program *program)
{
	char	*user_input;
	char	*prompt;

	prompt = get_user_prompt();
	user_input = readline(prompt);
	free(prompt);
	if (!user_input)
	{
		printf("exit\n");
		ft_free(program);
		ft_exit(1);
	}
	if (ft_strlen(user_input) != 0)
	{
		ft_strlcpy(input, user_input, MAXCOM - 1);
		add_history(user_input);
		free(user_input);
		return (0);
	}
	else
	{
		free(user_input);
		return (1);
	}
}