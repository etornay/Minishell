/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:10:25 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/11 18:42:45 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks()
{
	system("leaks -q minishell");
}

int	input(char *input, t_paco *p, char **env)
{
	t_parser	*node;

	p->lex = split_line(input, ' ', p);
	if (p->lex == NULL)
		return (printf("Unclosed quotes\n"), EXIT_SUCCESS);
	expand(p);
	if (p->lex != NULL)
	{
		p->lex2 = split_pipe(p->lex, p, -1, 0);
		free_lex(p);
	}
	if (p->lex2[0] == NULL)
		return (EXIT_SUCCESS);
	if (parser_cmd(p, 0) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	node = ((t_parser *)p->lst_cmd->content);
	if (executer(p, env, node) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (p->heredoc_flag == 1)
	{
		unlink("here_doc.tmp");
		p->heredoc_flag = 0;
	}
	return (EXIT_SUCCESS);
}

static int	minishell_exit(t_paco *p)
{
	signal(SIGINT, signals);
	signal(SIGQUIT, SIG_IGN);
	if (prompt(p) == EXIT_FAILURE)
	{
		printf("exit\n");
		exit(EXIT_FAILURE);
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
		minishell_exit(p);
		if (ft_strncmp(p->line, "\0", 1) == EXIT_FAILURE)
			add_history(p->line);
		if (input(p->line, p, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (p->line != NULL)
		{
			free(p->line);
			p->line = NULL;
		}
		if (p->lex2 != NULL)
			free_lex2(p);
		free_cmd_list(&p->lst_cmd);
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
	free_all(p);
	return (EXIT_SUCCESS);
}
