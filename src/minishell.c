/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:10:25 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/29 12:52:20 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks()
{
	system("leaks -q minishell");
}

static int	exec_builtins(t_paco *p)
{
	if (ft_strncmp(p->lex2[0], "pwd\0", 4) == EXIT_SUCCESS)
		exec_pwd(p);
	if (ft_strncmp(p->lex2[0], "env\0", 4) == EXIT_SUCCESS)
		exec_env(p);
	if (ft_strncmp(p->lex2[0], "export\0", 7) == EXIT_SUCCESS)
		exec_export(p, p->lex2, 1);
	if (ft_strncmp(p->lex2[0], "unset\0", 6) == EXIT_SUCCESS)
		exec_unset(p, p->lex2[1]);
	if (ft_strncmp(p->lex2[0], "echo\0", 5) == EXIT_SUCCESS)
		flag_echo(p->lex2, 0, p);
	if (ft_strncmp(p->lex2[0], "cd\0", 3) == EXIT_SUCCESS)
		exec_cd(p, p->lex2, 0);
	if (ft_strncmp(p->lex2[0], "exit\0", 5) == EXIT_SUCCESS)
	{
		free_path(p);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	input(char *input, t_paco *p, char **env)
{
	int	i;

	i = 0;
	(void)env;
	p->lex = split_line(input, ' ', p);
	expand(p);
	if (p->lex != NULL)
	{
		p->lex2 = split_pipe(p->lex, p, -1, 0);
		free_lex(p);
	}
	/*while (p->lex2[i])
	{
		printf("%s\n", p->lex2[i]);
		i++;
	}*/
	if (p->lex2[0] == NULL)
		return (EXIT_SUCCESS);
	parser_cmd(p, 0);
	t_list	*aux;
	aux = p->lst_cmd;
	int	j;
	while (aux != NULL)
	{
		j = 0;
		printf("Nodo \n");
		printf("path: %s\n", ((t_parser *)(aux->content))->full_path);
		while (((t_parser *)(aux->content))->full_cmd[j] != NULL)
		{
			printf("cmd: %s\n", ((t_parser *)(aux->content))->full_cmd[j]);
			j++;
		}
		printf("infile: %d\n", ((t_parser *)(aux->content))->infile);
		printf("outfile: %d\n", ((t_parser *)(aux->content))->outfile);
		aux = aux->next;
	}
	exec_builtins(p);
	free_cmd_list(&p->lst_cmd);
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
		if (p->lex2 != NULL)
			free_lex2(p);
		if (p->line != NULL)
		{
			free(p->line);
			p->line = NULL;
		}
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
