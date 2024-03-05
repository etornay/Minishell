/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:38:29 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/05 13:09:34 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser_cmd(t_paco *p, int i)
{
	t_parser	*node;

	while (p->lex2[i])
	{
		while (p->lex2[i] && p->lex2[i][0] != '|' && p->lex2[i] != NULL)
		{
			node = ft_calloc(1, sizeof(t_parser));
			node->outfile = 1;
			node->infile = 0;
			while (p->lex2[i] && p->lex2[i][0] != '|' && p->lex2[i][0] != '<' && p->lex2[i][0] != '>' && p->lex2[i] != NULL)
			{
				if (p->lex2[i][0] != '|' && p->lex2[i][0] != '<'
					&& p->lex2[i][0] != '>' && p->lex2[i] && i <= p->count)
					get_cmd(p, node, &i);
				if (node->full_cmd && check_builtin(p) == EXIT_FAILURE)
					path_cmd(p, node);
				else if (check_builtin(p) == EXIT_SUCCESS)
					node->full_path = NULL;
				while (p->lex2[i] && p->lex2[i][0] != '|'
					&& p->lex2[i][0] != '<' && p->lex2[i][0] != '>')
					i++;
			}
			p_utils(p, node, &i);
			pass_tokens(p, &i);
			ft_lstadd_back(&p->lst_cmd, ft_lstnew(node));
		}
		if (flag_pipe(p, &i) == EXIT_FAILURE)
			return ;
		if (i >= p->count)
			break ;
	}
}
