/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:54:45 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/08 18:38:39 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_oldpwd(t_paco *p)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, "OLDPWD", 6) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		p->aux = p->aux->next_env;
	}
	return (EXIT_FAILURE);
}

void	restart_index(t_paco *p)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		p->aux->index = 0;
		p->aux = p->aux->next_env;
	}
}

void	lstadd_oldpwd(t_paco *p)
{
	t_env	*old;
	char	dir[500];

	old = malloc(sizeof(t_env));
	if (!old)
		return ;
	getcwd(dir, 500);
	old->next_env = NULL;
	old->content = ft_strjoin("=", dir);
	old->name = "OLDPWD";
	old->index = 0;
	p->aux = p->l_env;
	while (p->aux->next_env)
		p->aux = p->aux->next_env;
	p->aux->next_env = old;
}

void	gen_oldpwd(t_paco *p)
{
	restart_index(p);
	lstadd_oldpwd(p);
	set_env_index(p);
}
