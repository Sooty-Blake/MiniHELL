/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:17:23 by bburston          #+#    #+#             */
/*   Updated: 2023/10/06 15:17:24 by bburston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int exit_number)
{
	exit(exit_number);
}

void	ft_free(t_program *program)
{
	ft_token_free(program);
	ft_free_envar(program);
}

void	ft_token_free(t_program *program)
{
	int	i;

	i = 0;
	if (program->token)
	{
		while (program->token[i])
		{
			free(program->token[i]);
			i++;
		}
		if (program->token)
			free(program->token);
	}
}

void	ft_free_envar(t_program *program)
{
	t_envar	*temp;
	int		i;

	i = 0;
	while (program->envar != 0)
	{
		temp = program->envar;
		program->envar = program->envar->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}