/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:09:40 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/04 21:03:15 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd_list(t_list **lst)
{
	t_list	*aux;
	int		i;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		i = -1;
		if (((t_parser *)((*lst)->content))->full_cmd)
		{
			while (((t_parser *)((*lst)->content))->full_cmd[++i])
				free(((t_parser *)((*lst)->content))->full_cmd[i]);
		}
		free(((t_parser *)((*lst)->content))->full_cmd);
		free(((t_parser *)((*lst)->content))->full_path);
		if (((t_parser *)((*lst)->content))->infile != 0)
			close(((t_parser *)((*lst)->content))->infile);
		if (((t_parser *)((*lst)->content))->outfile != 1)
			close(((t_parser *)((*lst)->content))->outfile);
		free(((t_parser *)((*lst)->content)));
		free((*lst));
		*lst = aux;
	}
	*lst = NULL;
}

void	free_lex2(t_paco *p)
{
	int	i;

	i = 0;
	if (p->lex2 != NULL)
	{
		while (p->lex2[i])
		{
			free(p->lex2[i]);
			p->lex2[i++] = NULL;
		}
		free(p->lex2);
		p->lex2 = NULL;
	}
}

void	free_split(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free (tmp);
}

void	free_cd_error(t_paco *p)
{
	free(p->tmp);
	free(p->cd_error);
}
