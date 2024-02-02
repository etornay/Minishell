/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 08:51:03 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/02 15:46:57 by etornay-         ###   ########.fr       */
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

	index = 0;
	p->aux = p->l_env;
	while (index <= ft_env_size(p->l_env))
	{
		while (p->aux != NULL)
		{
			if (ft_exp_cmp(p->l_env->name, p->aux->name) < 0
				&& p->aux->index == 0)
			{
				first = p->aux;
				p->aux = first;
			}
			p->aux = p->aux->next_env;
		}
		p->aux = p->l_env;
		first->index = index;
		p->aux = p->l_env;
		index++;
	}
}

/* void	exec_echo(char **s, int size)
{
	int	i;

	i = 0;
	while (s[size][i])
	{
		ft_printf()
	}
}

void	pecho(char **s, int flag)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i > 1)
	{
		if (ft_strncmp (s[2], "-n\0", 3) == EXIT_FAILURE)
		{
			flag = 1;
			i = 3;
		}
		else
			i = 2;
		while (s[i] != NULL)
		{
			exec_echo(s, i);
			i++;
		}
	}
	if (flag == 0)
		ft_printf("\n");
}
 */