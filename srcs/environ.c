/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:36:47 by bburston          #+#    #+#             */
/*   Updated: 2023/10/05 13:36:49 by bburston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envar	*split_env_var(char **envp)
{
	char	**split_env;
	t_envar	*start;
	t_envar	*end;
	t_envar	*new_node;
	int		i;

	i = 0;
	start = NULL;
	end = NULL;

	while (envp[i])
	{
		split_env = ft_split(envp[i], '=');
		new_node = init_env(split_env[0], split_env[1]);
		if (new_node == NULL)
			printf("Error: memory not allocated\n");
		if (start == NULL)
			start = new_node;
		if (end != NULL)
			end->next = new_node;
		end = new_node;
		i++;
		free_new_split(split_env);
	}
	return (start);
}

void	add_env_var(t_envar *node, t_program *program)
{
	t_envar	*tmp;

	tmp = program->envar;
	while (tmp != NULL)
	{
		if (strcmp(tmp->name, node->name) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(node->value);
			rebuild_envp(program);
			return ;
		}
		tmp = tmp->next;
	}
	if (program->envar == NULL)
		program->envar = node;
	else
		add_env_var_norm(program, tmp, node);
	tmp = program->envar;
	while (tmp != NULL)
		tmp = tmp->next;
	rebuild_envp(program);
}

void	free_new_split(char **split_env)
{
	int	i;

	i = 0;
	while (split_env[i])
	{
		free(split_env[i]);
		i++;
	}
	free(split_env);
}