/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:40:49 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/07 11:01:33 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*get_first(t_paco *p)
{
	t_env	*first;
	int		i;

	i = 1;
	p->aux = p->l_env;
	first = p->l_env;
	while (p->aux != NULL)
	{
		if (ft_exp_cmp(first->name, p->aux->name) < 0
			&& p->aux->index == 0)
			first = p->aux;
		p->aux = p->aux->next_env;
	}
	return (first);
}

void	set_env_index(t_paco *p)
{
	int		index;

	index = 1;
	p->first = p->l_env;
	while (index <= ft_env_size(p->l_env))
	{
		p->aux = p->l_env;
		while (p->aux != NULL)
		{
			if (ft_exp_cmp(p->first->name, p->aux->name) > 0
				&& p->aux->index == 0)
				p->first = p->aux;
			p->aux = p->aux->next_env;
		}
		p->first->index = index;
		p->first = get_first(p);
		index++;
	}
}
