/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:10:25 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/05 11:52:35 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input(char *input, t_paco *p, char **env)
{
	int	i;

	i = 0;
	(void)env;
	p->lex = split_line(input, ' ', p);
	while (p->lex[i] != NULL)
	{
		ft_printf("%s\n", p->lex[i]);
		i++;
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
		/*if (input(p->line, p, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);*/
		if (ft_strncmp(p->line, "pwd", 3) == EXIT_SUCCESS)
			pwd(p);
		if (ft_strncmp(p->line, "exit", 4) == EXIT_SUCCESS)
			exit(EXIT_SUCCESS);
		if (ft_strncmp(p->line, "env", 3) == EXIT_SUCCESS)
			exec_env(p);
		if (ft_strncmp(p->line, "export", 6) == EXIT_SUCCESS)
			exec_export(p);
		if (ft_strncmp(p->line, "echo", 4) == EXIT_SUCCESS)
		{
			if (ft_strncmp(p->line, "echo -n", 7) == EXIT_SUCCESS)
				exec_echo(p, 1);
			else
				exec_echo(p, 0);
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_paco	*p;

	(void)argc;
	(void)argv;
	p = ft_calloc(1, sizeof(t_paco));
	if (p == NULL)
		exit (EXIT_FAILURE);
	init_struct(p);
	if (minishell(p, env) == EXIT_FAILURE)
		exit (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}
