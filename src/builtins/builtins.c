/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 08:51:03 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/05 19:05:23 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	first = p->l_env;
	p->aux = p->l_env;
	while (index <= ft_env_size(p->l_env))
	{
		while (p->aux != NULL)
		{
			if (ft_exp_cmp(p->l_env->name, p->aux->name) < 0
				&& p->aux->index == 0)
				first = p->aux;
			p->aux = p->aux->next_env;
		}
		first->index = index;
		p->aux = p->l_env;
		index++;
	}
}

static void	exec_echo2(char **s, int size, t_paco *p, int *j)
{
	while (s[size][*j])
	{
		if (s[size][*j] == '\"' && p->double_flag && !p->simple_flag)
			(*j)++;
		else if (s[size][*j] == '\'' && p->simple_flag && !p->double_flag)
			(*j)++;
		else if (s[size][*j] == '\"' && !p->double_flag && p->simple_flag)
		{
			ft_printf("%c", s[size][*j]);
			(*j)++;
		}
		else if (s[size][*j] == '\'' && !p->simple_flag && p->double_flag)
		{
			ft_printf("%c", s[size][*j]);
			(*j)++;
		}
		else
		{
			ft_printf("%c", s[size][*j]);
			(*j)++;
		}
	}
}

static void	exec_echo(char **s, int size, t_paco *p)
{
	int	j;

	j = 0;
	if (s[size][j] == '\0')
		ft_printf("%c", s[size][j]);
	else if (s[size][j] == '\"' && !p->simple_flag)
	{
		j++;
		p->double_flag = !p->double_flag;
	}
	else if (s[size][j] == '\'' && !p->double_flag)
	{
		j++;
		p->simple_flag = !p->simple_flag;
	}
	exec_echo2(s, size, p, &j);
}

void	pecho(char **s, int flag, t_paco *p)
{
	while (s[p->j])
		p->j++;
	if (p->j > 1)
	{
		if (ft_strncmp (s[1], "-n\0", 3) == EXIT_SUCCESS)
		{
			flag = 1;
			p->j = 2;
		}
		else
			p->j = 1;
		while (s[p->j] != NULL)
		{
			exec_echo(s, p->j, p);
			if (s[p->j + 1])
				ft_printf(" ");
			p->j++;
			if (p->double_flag == 1)
				p->double_flag = 0;
			if (p->simple_flag == 1)
				p->simple_flag = 0;
		}
	}
	if (flag == 0)
		ft_printf("\n");
}
