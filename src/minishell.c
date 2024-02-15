/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:10:25 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/15 14:41:19 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks()
{
	system("leaks -q minishell");
}

int	input(char *input, t_paco *p, char **env)
{
	int	i;

	i = 0;
	(void)env;
	p->lex = split_line(input, ' ', p);
	/* p->lex = ft_split_mini(input, ' '); */
	expand(p);
	if (p->lex[0] == NULL)
		return (EXIT_SUCCESS);
	if (ft_strncmp(p->lex[0], "pwd\0", 4) == EXIT_SUCCESS)
		exec_pwd(p);
	if (ft_strncmp(p->lex[0], "env\0", 4) == EXIT_SUCCESS)
		exec_env(p);
	if (ft_strncmp(p->lex[0], "export\0", 7) == EXIT_SUCCESS)
		exec_export(p, p->lex);
	if (ft_strncmp(p->lex[0], "unset\0", 6) == EXIT_SUCCESS)
		exec_unset(p, p->lex[1]);
	if (ft_strncmp(p->lex[0], "echo\0", 5) == EXIT_SUCCESS)
		flag_echo(p->lex, 0, p);
	if (ft_strncmp(p->lex[0], "cd\0", 3) == EXIT_SUCCESS)
		exec_cd(p, p->lex);
	if (ft_strncmp(p->lex[0], "exit\0", 5) == EXIT_SUCCESS)
	{
		free_path(p);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	minishell(t_paco *p, char **env)
{
	ft_paco_sanz();
	if (get_path(p, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_env(p, env, 0);
	while (33)
	{
		if (prompt(p) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (ft_strncmp(p->line, "\0", 1) == EXIT_FAILURE)
			add_history(p->line);
		if (input(p->line, p, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (p->lex != NULL)
			free_lex(p);
		if (p->line != NULL)
		{
			free(p->line);
			p->line = NULL;
		}
		restart_index(p);
		set_env_index(p);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_paco	*p;

	(void)argc;
	(void)argv;
	atexit(ft_leaks);
	p = ft_calloc(1, sizeof(t_paco));
	if (p == NULL)
		exit (EXIT_FAILURE);
	init_struct(p);
	if (minishell(p, env) == EXIT_FAILURE)
	{
		free_all(p);
		exit(EXIT_FAILURE);
	}
	return (free_all(p), EXIT_SUCCESS);
}
