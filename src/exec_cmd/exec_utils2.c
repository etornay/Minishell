/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:07:02 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/12 12:15:48 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_errors(t_paco *p, t_parser *node, t_list *aux)
{
	if (node->infile == -1 || node->outfile == -1)
	{
		if (p->lex2[0][0] == '<' || p->lex2[0][0] == '>')
			printf("PACOSHELL: %s: No such file or directory\n", p->lex2[1]);
		else
			printf("PACOSHELL: %s: No such file or directory\n", p->lex2[2]);
		aux = aux->next;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	msg_err(char *str)
{
	perror(str);
	unlink("here_doc.tmp");
	return (EXIT_FAILURE);
}
