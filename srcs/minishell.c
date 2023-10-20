/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:52:24 by bburston          #+#    #+#             */
/*   Updated: 2023/09/18 20:46:40 by bburston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;

int		main(int ac, char **av, char **envp)
{
	char		input[MAXCOM];
	t_token		*root;
	t_program	program;

	(void)ac;
	(void)av;
	root = NULL;
	init_program(&program, envp);
	sig_init();
	while (1)
	{
		if (take_input(input, &program) == 0)
		{
			program.redirect_index = 0;
			//...
		}
	}
}