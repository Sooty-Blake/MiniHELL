/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:32:45 by bburston          #+#    #+#             */
/*   Updated: 2023/10/05 14:32:48 by bburston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rebuild_envp(t_program *program)
{
	char	*name_part;
	t_envar	*tmp;
	int		count;
	int		i;

	rebuild_envp_norm(program);
	tmp = program->envar;
	count = count_envars(tmp);
	i = 0;
	program->envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!program->envp)
		return ;
	while (i < count)
	{
		name_part = ft_strjoin(tmp->name, "=");
		program->envp[i] = ft_strjoin(name_part, tmp->value);
		free(name_part);
		i++;
		tmp = tmp->next;
	}
	program->envp[i] = NULL;
}

void	rebuild_envp_norm(t_program *program)
{
	int	i;

	i = 0;
	if (program->envp != 0)
	{
		while (program->envp[i] != 0)
		{
			free(program->envp[i]);
			i++;
		}
		if (program->envp)
			free(program->envp);
	}
}

int		count_envars(t_envar *envars)
{
	int		i;
	t_envar	*tmp;

	tmp = envars;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}