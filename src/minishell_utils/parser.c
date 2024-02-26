/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:38:29 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/26 13:13:13 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	p_utils(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i][0] == '>')
		exec_append(p, node, i);
	else if (p->lex[*i] && p->lex[*i][0] == '>' && p->lex[*i + 1])
		exec_trunc(p, node, i);
	else if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1][0] == '<')
		exec_heredoc(p, node);
	else if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1])
		read_only(p, node, i);
}

static void	parser_cmd3(t_paco *p, t_parser *node, int *i)
{
	p_utils(p, node, i);
	if (p->lex2[*i] && p->lex2[*i][0] == '|')
		flag_pipe(p, i);
	else if (p->lex2[*i] && ((p->lex2[*i][0] == '>' && p->lex2[*i + 1][0] == '>'
		&& p->lex2[*i + 2]) || (p->lex2[*i][0] == '<'
		&& p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2])))
		i += 3;
	else if ((p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex[*i + 1])
		|| (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex[*i + 1]))
		i += 2;
	if (p->lex2[*i][0] != '|' && p->lex2[*i][0] != '<'
		&& p->lex2[*i][0] != '>' && p->lex2[*i])
		get_cmd(p, node);
	if (node->full_cmd)
		path_cmd(p, node, i);
	while (p->lex2[*i] && p->lex2[*i][0] != '|'
		&& p->lex2[*i][0] != '<' && p->lex2[*i][0] != '>')
		i++;
	while (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i][0] == '<')
		p_utils(p, node, i);
	ft_lstadd_back(&p->lst_cmd, ft_lstnew(node));
}

static void	parser_cmd2(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i][0] != '|' && p->lex2[*i][0] != '<'
		&& p->lex2[*i][0] != '>' && p->lex2[*i])
		get_cmd(p, node);
	if (node->full_cmd)
		path_cmd(p, node, i);
	while (p->lex2[*i] && p->lex2[*i][0] != '|'
		&& p->lex2[*i][0] != '<' && p->lex2[*i][0] != '>')
		i++;
	p_utils(p, node, i);
	if (p->lex2[*i] && p->lex2[*i][0] == '|')
		flag_pipe(p, i);
	else if (p->lex2[*i] && ((p->lex2[*i][0] == '>' && p->lex2[*i + 1][0] == '>'
		&& p->lex2[*i + 2]) || (p->lex2[*i][0] == '<'
		&& p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2])))
		i += 3;
	else if ((p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex[*i + 1])
		|| (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex[*i + 1]))
		i += 2;
	while (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i][0] == '<')
		p_utils(p, node, i);
	ft_lstadd_back(&p->lst_cmd, ft_lstnew(node));
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
		if (p->lex2[i] && p->lex2[i][0] != '|' && p->lex2[i][0] != '<'
			&& p->lex2[i][0] != '>')
			parser_cmd2(p, node, &i);
		else if (p->lex2[i] && (p->lex2[i][0] == '<' && p->lex2[i][0] == '>'))
			parser_cmd3(p, node, &i);
		else
			i++;
	}
}
