/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:49:31 by bburston          #+#    #+#             */
/*   Updated: 2023/10/05 13:49:32 by bburston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp_first_run(t_program *program, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[j])
		j++;
	program->envp = (char **)malloc(sizeof(char *) * (j + 1));
	while (i < j)
	{
		program->envp[i] = ft_strdup(envp[i]);
		i++;
	}
}

void	add_env_var_norm(t_program *program, t_envar *tmp, t_envar *node)
{
	tmp = program->envar;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}