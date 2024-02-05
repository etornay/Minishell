/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 08:51:03 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/05 09:31:43 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_paco *p)
{
	char	dir[500];

	p->act_dir = getcwd(dir, 500);
	if (p->act_dir == NULL)
		return ;
	ft_printf("%s\n", p->act_dir);
}

void	exec_export(t_paco *p)
{
	int		index;

	p->aux = p->l_env;
	index = 1;
	while (index <= ft_env_size(p->aux))
	{
		if (p->aux->index == index)
		{
			ft_printf("%s%s\n", p->aux->name, p->aux->content);
			p->aux = p->l_env;
			index++;
		}
		else
			p->aux = p->aux->next_env;
	}
}

void	set_env_index(t_paco *p)
{
	int		index;
	t_env	*first;

	index = 1;
	p->aux = p->l_env;
	first = p->l_env;
	while (index <= ft_env_size(p->l_env))
	{
		while (p->aux != NULL)
		{
			if (ft_strncmp(p->aux->name, first->name,
					ft_strlen(p->aux->name)) < 0 && p->aux->index == 0)
				first = p->aux;
			p->aux = p->aux->next_env;
		}
		p->aux = p->l_env;
		first->index = index;
		index++;
	}
}

void	exec_unset(t_paco *p, char *name)
{
	t_env	*aux;
	t_env	*del;
	t_env	*prev;

	if (!name)
		return ;
	aux = p->l_env;
	prev = NULL;
	while (aux != NULL)
	{
		if (!ft_strncmp(aux->name, name, ft_strlen(name)))
		{
			del = aux;
			if (prev)
				prev->next_env = aux->next_env;
			else
				p->l_env = aux->next_env;
			free(del->name);
			free(del->content);
			free(del);
			break ;
		}
		prev = aux;
		aux = aux->next_env;
	}
}
