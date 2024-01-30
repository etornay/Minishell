/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:10:25 by etornay-          #+#    #+#             */
/*   Updated: 2024/01/30 13:29:01 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input(char *input, t_paco *p, char **env)
{
	(void)env;
	p->lex = split_line(input, ' ');
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
			exit (EXIT_FAILURE);
		if (ft_strncmp(p->line, "\0", 1) == EXIT_FAILURE)
			add_history(p->line);
		if (input(p->line, p, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_strncmp(p->line, "pwd", 3) == EXIT_SUCCESS)
			pwd(p);
		if (ft_strncmp(p->line, "exit", 4) == EXIT_SUCCESS)
			exit(EXIT_SUCCESS);
		/* if (ft_strncmp(p->line, "echo", 4) == EXIT_SUCCESS)
		{
			if (ft_strncmp(p->line, "echo -n", 7) == EXIT_SUCCESS)
				echo(p, 1);
			else
				echo(p, 0);
		} */
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
