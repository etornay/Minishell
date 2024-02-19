/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:01:33 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/19 12:22:16 by ncruz-ga         ###   ########.fr       */
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
	p->tmp = NULL;
	p->cd_error = NULL;
	p->double_flag = 0;
	p->simple_flag = 0;
	p->i = 0;
	p->c = 0;
	p->j = 0;
	p->count = 0;
	p->wc = 1;
}
