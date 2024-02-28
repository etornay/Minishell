/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:30:18 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/28 12:14:38 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	path_cmd(t_paco *p, t_parser *node, int *i)
{
	p->j = -1;
	while (p->path[++p->j] != NULL)
	{
		p->tmp_cmd = ft_strjoin(p->path[p->j], "/");
		p->tmp_path = ft_strjoin(p->tmp_cmd, node->full_cmd[*i]);
		if (!p->tmp_path || !p->tmp_cmd)
			return (EXIT_FAILURE);
		free(p->tmp_cmd);
		if (access(p->tmp_path, F_OK) == 0
			&& access(p->tmp_path, X_OK) == 0)
		{
			node->full_path = ft_strdup(p->tmp_path);
			p->tmp_path = NULL;
			break ;
		}
		free(p->tmp_path);
	}
	return (EXIT_SUCCESS);
}

void	get_cmd(t_paco *p, t_parser *node, int *k)
{
	int	j;
	int	i;

	j = 0;
	i = *k;
	while (p->lex2 && p->lex2[i] != NULL && p->lex2[i][0] != '|'
		&& p->lex2[i][0] != '<' && p->lex2[i][0] != '>')
		i++;
	node->full_cmd = ft_calloc(i + 1, sizeof(char *));
	while (j < i)
	{
		node->full_cmd[j] = ft_strdup(p->lex2[*k]);
		j++;
	}
	node->full_cmd[j] = NULL;
}

void	p_utils(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i] && p->lex2[*i][0] == '>'
		&& p->lex2[*i + 1][0] == '>' && p->lex2[*i + 2][0] != '>')
		exec_append(p, node, i);
	else if (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i + 1])
		exec_trunc(p, node, i);
	else if (p->lex2[*i] && p->lex2[*i][0] == '<'
		&& p->lex2[*i + 1][0] == '<' && p->lex2[*i + 2][0] != '<')
		exec_heredoc(p, node, i);
	else if (p->lex2[*i] && p->lex2[*i][0] == '<' && p->lex2[*i + 1])
		read_only(p, node, i);
}