/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:19:31 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/07 13:27:08 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	pwd(t_paco *p)
{
	char	dir[500];

	p->act_dir = getcwd(dir, 500);
	if (p->act_dir == NULL)
		return ;
	ft_printf("%s\n", p->act_dir);
}

void	exec_cd(t_paco *p, char **s)
{
	char	*path;

	if (ft_strncmp(s[0], "cd\0", 3) && s[1] == NULL)
	{
		path = get_env(p, "HOME");
	}
	else if (ft_strncmp(s[0], "cd\0", 3) && ft_strncmp(s[1], "-\0", 2))
	{
		
	}
	else if (ft_strncmp(s[0], "cd\0", 3) && s[2] != NULL)
	{
		
	}
}
