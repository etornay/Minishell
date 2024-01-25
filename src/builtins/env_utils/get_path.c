/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:11:15 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/01/25 10:02:26 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_path(t_paco *p, char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	p->path = ft_split(env[i] + 5, ":");
	if (!p->path)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	lst_addenv_back(t_env **lst, t_env *new, char **tmp)
{
	t_env	*first;

	if (new == NULL)
		return ;
	if (tmp != NULL)
	{
		new->name = tmp[0];
		new->content = tmp[1];
		new->index = 0;
		new->next_env = NULL;
	}
	first = lst;
	if (first == NULL)
	{
		first = new;
		return ;
	}
	while (first->next != NULL)
		first = first->next;
	first->next = new;
	return ;
}

void	init_env(t_paco *p, char **env, int i)
{
	char	**tmp;

	p->l_env = calloc(1, sizeof(t_env));
	if (!p->l_env)
		return (EXIT_FAILURE);
	tmp = ft_split(env[i], '=');
	if (!tmp)
		return ;
	p->l_env->name = ft_strdup(tmp[0]);
	p->l_env->content = ft_strjoin("=", tmp[1]);
	p->l_env->next_env = NULL;
	p->l_env->index = 0;
	free_split(tmp);
	while (tmp[++i] != NULL)
	{
		p->aux = ft_calloc(1, sizeof(t_env));
		if (!p->aux)
			return ;
		tmp = ft_split(env[i], '=');
		if (!tmp)
			return ;
		lst_addenv_back(&p->envp, p->aux, tmp);
		free_split(tmp);
	}
	
}
