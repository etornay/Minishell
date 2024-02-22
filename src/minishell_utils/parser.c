/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:38:29 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/22 10:27:15 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append(t_paco *p, t_parser *node, int i)
{
	if (p->lex2[i + 2])
	{
		node->outfile = open(p->lex2[i + 2], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (node->outfile > 0)
			return ;
	}
	else
	{
		p->clean = ft_lstnew(node);
		free_cmd_list(p->clean);
		printf("bash: syntax error near unexpected token `newline'\n");
		return ;
	}
}

void	path_cmd(t_paco *p, t_parser *node, int i, int j)
{
	node->full_path = ft_calloc(len, sizeof(char *));
	if (!node->full_path)
		return (EXIT_FAILURE);
	while (node->full_cmd[i] != NULL)
	{
		j = -1;
		while (p->path[++p->j] != NULL)
		{
			p->tmp_cmd = ft_strjoin(p->path[j], "/");
			p->tmp_path = ft_strjoin(p->tmp_cmd, node->full_cmd[i][0]);
			if (!p->tmp_path || !p->tmp_cmd)
				return (EXIT_FAILURE);
			free(p->tmp_cmd);
			if (access(p->tmp_path, F_OK) == 0
				&& access(p->tmp_path, X_OK) == 0)
			{
				node->full_path[i] = p->tmp_path;
				p->tmp_path = NULL;
				break ;
			}
			free(p->tmp_path);
		}
	}
	return (node->full_path[i] = NULL, EXIT_SUCCESS);
}

void	get_cmd(t_paco *p, t_parser *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (p->lex2[i][0] != '|' && p->lex2[i][0] != '<'
		&& p->lex2[i][0] != '>' && p->lex2)
		i++;
	node->full_cmd = ft_calloc(i + 1, sizeof(char *));
	while (j < i)
	{
		node->full_cmd[j] = ft_strdup(p->lex2[j]);
		j++;
	}
	node->full_cmd[j] = NULL;
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
		node = ft_calloc(1, sizeof(parser));
		node->outfile = 1;
		node->infile = 0;
		if (p->lex2[i][0] != '|' && p->lex2[i][0] != '<' && p->lex2[i][0] != '>')
		{
			if (p->lex2)
				get_cmd(p, node);
			if (node->full_cmd)
				path_cmd(p, node, i, j);
			while (p->lex2[i][0] != '|' && p->lex2[i][0] != '<' && p->lex2[i][0] != '>')
				i++;
			if (p->lex2[i] && p->lex2[i][0] == '>' && p->lex[i + 1][0] == '>')
			{
				append()
			}
		}
	}
}
