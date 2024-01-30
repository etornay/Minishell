/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:01:33 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/01/30 13:24:32 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_paco *p)
{
	p->shell = NULL;
	p->act_dir = NULL;
	p->aux = NULL;
	p->l_env = NULL;
	p->line = NULL;
	p->path = NULL;
	p->lex = NULL;
}
