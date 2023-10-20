/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburston <bburston@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:20:00 by bburston          #+#    #+#             */
/*   Updated: 2023/09/18 15:15:05 by bburston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* libraries */
# include "../libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>

# define MAXCOM 5000
# define MAXLIST 100
# define MAX_BUFFER 4096
# define T_DEFAULT	"\033[0m"

/* global exit status variable */
extern int	g_exit_status;

/* structs */
typedef struct s_token
{
	char			*data;
	struct s_token	*next;
}   t_token;

typedef struct s_program
{
	struct s_envar	*envar;
	char			**token;
	char			**envp;
	char			*redirect_in;
	char			*redirect_out;
	int				redirect_index;
	int				out_file;
	int				out_backup;
	int				in_file;
	int				in_backup;
	int				redir_out_flag;
	int				redir_in_flag;
}	t_program;

typedef struct s_envar
{
	char			*name;
	char			*value;
	struct s_envar	*next;
} t_envar;

/* commands */

/* init.c */
void		init_program(t_program *program, char **envp);
t_envar		*init_env(char *name, char *value);
void		init_env_vars(t_program *program);
int			take_input(char *input, t_program *program);


/* environ.c */
t_envar		*split_env_var(char **envp);
void		add_env_var(t_envar *node, t_program *program);
void		free_new_split(char **split_env);

/* utils.c */
void		init_envp_first_run(t_program *program, char **envp);
void		add_env_var_norm(t_program *program, t_envar *tmp, t_envar *node);

/* environ_utils.c */
void		rebuild_envp(t_program *program);
void		rebuild_envp_norm(t_program *program);
int			count_envars(t_envar *envars);

/* signal.c */
void		sig_init(void);
void		sig_handler(int sig);

/* free_and_exit.c */
void		ft_exit(int exit_number);
void		ft_free(t_program *program);
void		ft_token_free(t_program *program);
void		ft_free_envar(t_program *program);

#endif