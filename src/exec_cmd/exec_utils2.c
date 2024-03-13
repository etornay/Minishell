/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:07:02 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/13 14:16:44 by etornay-         ###   ########.fr       */
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
		return (g_status = 1, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	msg_err(char *str)
{
	perror(str);
	unlink("here_doc.tmp");
	return (EXIT_FAILURE);
}

int	check_f_d(t_parser *node)
{
	struct stat	file_info;
	int			i;

	i = 1;
	while (node->full_cmd[i] && ft_strchr(node->full_cmd[i], '-'))
		i++;
	if (stat(node->full_cmd[i], &file_info) == 0 || node->full_cmd[i] == 0)
		return (1);
	return (0);
}
