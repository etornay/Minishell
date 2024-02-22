/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:01:33 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/22 15:04:51 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_struct(t_paco *p)
{
	p->shell = NULL;
	p->act_dir = NULL;
	p->aux = NULL;
	p->l_env = NULL;
	p->line = NULL;
	p->path = NULL;
	p->lex = NULL;
	p->lex2 = NULL;
	p->tmp = NULL;
	p->cd_error = NULL;
	p->eof = NULL;
	p->heredoc_line = NULL;
	p->dup_stdin = dup(STDIN_FILENO);
	p->double_flag = 0;
	p->simple_flag = 0;
	p->pipe_flag = 0;
	p->i = 0;
	p->c = 0;
	p->j = 0;
	p->count = 0;
	p->wc = 1;
	p->wordle = 0;
	p->n_split = 0;
	p->l = 0;
	p->heredoc_flag = 0;
	p->heredoc_flag = 0;
}
