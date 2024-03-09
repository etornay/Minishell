/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:10:25 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/09 17:54:24 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks()
{
	system("leaks -q minishell");
}

int	input(char *input, t_paco *p, char **env)
{
	p->lex = split_line(input, ' ', p);
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
	/*t_list	*aux;
	aux = p->lst_cmd;
	int	j;
	while (aux != NULL)
	{
		j = 0;
		printf("Nodo \n");
		printf("path: %s\n", ((t_parser *)(aux->content))->full_path);
		if (((t_parser *)(aux->content))->full_cmd != NULL)
		{
			while (((t_parser *)(aux->content))->full_cmd[j] != NULL)
			{
				printf("cmd: %s\n", ((t_parser *)(aux->content))->full_cmd[j]);
				j++;
			}
		}
		printf("infile: %d\n", ((t_parser *)(aux->content))->infile);
		printf("outfile: %d\n", ((t_parser *)(aux->content))->outfile);
		aux = aux->next;
	}*/
	if (executer(p, env) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (p->heredoc_flag == 1)
	{
		unlink("here_doc.tmp");
		p->heredoc_flag = 0;
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
		signal(SIGINT, signals);
		signal(SIGQUIT, SIG_IGN);
		if (prompt(p) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
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
