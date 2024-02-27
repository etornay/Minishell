/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:38:29 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/27 17:01:24 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	p_utils(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i + 1][0] == '>' && p->lex2[*i + 2][0] != '>')
		exec_append(p, node, i);
	else if (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i + 1])
		exec_trunc(p, node, i);
	else if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2][0] != '<')
		exec_heredoc(p, node, i);
	else if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1])
		read_only(p, node, i);
}

static int	parser_cmd3(t_paco *p, t_parser *node, int *i)
{
	p_utils(p, node, i);
	if (p->lex2[*i] && p->lex2[*i][0] == '|')
	{
		if (flag_pipe(p, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && ((p->lex2[*i][0] == '>' && p->lex2[*i + 1][0] == '>'
		&& p->lex2[*i + 2]) || (p->lex2[*i][0] == '<'
		&& p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2])))
		(*i) += 3;
	else if ((p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex[*i + 1])
		|| (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex[*i + 1]))
		(*i) += 2;
	if (p->lex2[*i][0] != '|' && p->lex2[*i][0] != '<'
		&& p->lex2[*i][0] != '>' && p->lex2[*i])
		get_cmd(p, node, i);
	if (node->full_cmd)
		path_cmd(p, node, i);
	while (p->lex2[*i] && p->lex2[*i][0] != '|'
		&& p->lex2[*i][0] != '<' && p->lex2[*i][0] != '>')
		(*i)++;
	while (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i][0] == '<')
		p_utils(p, node, i);
	ft_lstadd_back(&p->lst_cmd, ft_lstnew(node));
	return (EXIT_SUCCESS);
}

static int	parser_cmd2(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i][0] != '|' && p->lex2[*i][0] != '<'
		&& p->lex2[*i][0] != '>' && p->lex2[*i])
		get_cmd(p, node, i);
	if (node->full_cmd && check_builtin(p) == EXIT_FAILURE)
		path_cmd(p, node, i);
	else if (check_builtin(p) == EXIT_SUCCESS)
		node->full_path = NULL;
	while (p->lex2[*i] && p->lex2[*i][0] != '|'
		&& p->lex2[*i][0] != '<' && p->lex2[*i][0] != '>')
		(*i)++;
	p_utils(p, node, i);
	if (p->lex2[*i] && p->lex2[*i][0] == '|')
	{
		if (flag_pipe(p, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && ((p->lex2[*i][0] == '>' && p->lex2[*i + 1][0] == '>'
		&& p->lex2[*i + 2]) || (p->lex2[*i][0] == '<'
		&& p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2])))
		(*i) += 3;
	else if ((p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i + 1])
		|| (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1]))
		(*i) += 2;
	while (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i][0] == '<')
		p_utils(p, node, i);
	ft_lstadd_back(&p->lst_cmd, ft_lstnew(node));
	return (EXIT_SUCCESS);
}

static void	parser_cmd_special(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i] && p->lex2[0][0] == '>'
		&& p->lex2[1][0] == '>' && p->lex2[2] && p->lex2[2][0] != '>')
		exec_append(p, node, i);
	else if (p->lex2[*i] && p->lex2[0][0] == '>' && p->lex2[1]
		&& p->lex2[1][0] != '>')
		exec_trunc(p, node, i);
	else if (p->lex2[*i] && p->lex2[0][0] == '<'
		&& p->lex2[1][0] == '<' && p->lex2[2] && p->lex2[2][0] != '<')
		exec_heredoc(p, node, i);
	else if (p->lex2[*i] && p->lex2[0][0] == '<' && p->lex2[1]
		&& p->lex2[1][0] != '<')
		read_only(p, node, i);
	return ;
}

void	parser_cmd(t_paco *p)
{
	int			i;
	int			j;
	t_parser	*node;

	i = 0;
	j = 0;
	while (p->lex2[i])
	{
		node = ft_calloc(1, sizeof(t_parser));
		node->outfile = 1;
		node->infile = 0;
		if (p->lex2[i] && ((p->lex2[0][0] == '<' && p->lex2[1][0] == '<'
			&& p->lex2[2]) || (p->lex2[0][0] == '<' && p->lex2[1])
			|| (p->lex2[0][0] == '>' && p->lex2[1][0] == '>' && p->lex2[2])
			|| (p->lex2[0][0] == '>' && p->lex2[1])))
		{
			parser_cmd_special(p, node, &i);
			free(node);
			break ;
		}
		else if (p->lex2[i] && p->lex2[i][0] != '|' && p->lex2[i][0] != '<'
			&& p->lex2[i][0] != '>')
		{
			if (parser_cmd2(p, node, &i) == EXIT_FAILURE)
			{
				free(node);
				break ;
			}
		}
		else if (p->lex2[i] && (p->lex2[i][0] == '|'
			|| p->lex2[i][0] == '<' || p->lex2[i][0] == '>'))
		{
			if (parser_cmd3(p, node, &i) == EXIT_FAILURE)
			{
				free(node);
				break ;
			}
		}
		else
			i++;
	}
}
