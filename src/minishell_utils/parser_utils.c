/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:30:18 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/26 13:09:01 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	path_cmd(t_paco *p, t_parser *node, int *i)
{
	node->full_path = ft_calloc(1, sizeof(char *));
	if (!node->full_path)
		return (EXIT_FAILURE);
	while (node->full_cmd[*i] != NULL)
	{
		p->j = -1;
		while (p->path[++p->j] != NULL)
		{
			p->tmp_cmd = ft_strjoin(p->path[p->j], "/");
			p->tmp_path = ft_strjoin(p->tmp_cmd, &node->full_cmd[*i][0]);
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
	}
	return (node->full_path[*i] = '\0', EXIT_SUCCESS);
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
