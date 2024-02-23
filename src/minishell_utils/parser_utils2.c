/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:04:59 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/23 17:13:23 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	flag_pipe(t_paco *p, int *i)
{
	p->pipe_flag = 1;
	*i++;
}

void	read_only(t_paco *p, t_parser *node, int *i)
{
	node->infile = open(p->lex2[*i + 1], O_RDONLY);
	if (node->infile < 0)
		return ;
}

void	trunc(t_paco *p, t_parser *node, int *i)
{
	node->outfile = open(p->lex2[*i + 1], O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (node->outfile < 0)
		return ;
}

void	append(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i + 2])
	{
		node->outfile = open(p->lex2[*i + 2], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (node->outfile > 0)
			return ;
	}
	else
	{
		p->clean = ft_lstnew(node);
		free_cmd_list(&p->clean);
		printf("bash: syntax error near unexpected token `newline'\n");
		return ;
	}
}
