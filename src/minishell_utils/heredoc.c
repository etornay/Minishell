/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:10:25 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/27 13:57:30 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//NO CIERRA EL ARCHIVO TEMPORAL
static int	msg_error(char *str)
{
	perror(str);
	unlink("here_doc.tmp");
	return (EXIT_FAILURE);
}

void	ft_heredoc(t_paco *p, char *limit)
{
	p->eof = ft_strjoin(limit, "\n");
	p->heredoc_tmp = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (43)
	{
		write(1, "> ", 2);
		p->heredoc_line = get_next_line(p->dup_stdin);
		if (!p->heredoc_line)
			msg_error("Line");
		if (!ft_strncmp(p->eof, p->heredoc_line, ft_strlen(p->heredoc_line)))
		{
			free(p->eof);
			free(p->heredoc_line);
			p->heredoc_line = NULL;
			close(p->dup_stdin);
			get_next_line(p->dup_stdin);
			break ;
		}
		write(p->heredoc_tmp, p->heredoc_line, ft_strlen(p->heredoc_line));
		free(p->heredoc_line);
	}
	close(p->heredoc_tmp);
	p->heredoc_tmp = open("here_doc.tmp", O_RDONLY);
	p->dup_stdin = dup(STDIN_FILENO);
}

void	exec_heredoc(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i + 2])
	{
		p->heredoc_flag = 1;
		ft_heredoc(p, p->lex2[*i + 2]);
		node->infile = p->heredoc_tmp;
	}
	else if (p->lex2[*i] && p->lex2[0][0] == '<' && p->lex2[1][0] == '<' && p->lex2[2])
	{
		p->heredoc_flag = 1;
		ft_heredoc(p, p->lex2[2]);
		node->infile = p->heredoc_tmp;
	}
	else
	{
		p->clean = ft_lstnew(node);
		free_cmd_list(&p->clean);
		printf("bash: syntax error near unexpected token `newline'\n");
		return ;
	}
}