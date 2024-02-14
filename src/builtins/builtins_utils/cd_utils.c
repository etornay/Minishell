/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:50:53 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/02/12 10:11:12 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_cd_path(t_paco *p, char *s)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, s, ft_strlen(s)) == EXIT_SUCCESS)
		{
			p->tmp = p->aux->content + 1;
			break ;
		}
		p->aux = p->aux->next_env;
	}
}

void	change_pwd(t_paco *p)
{
	char	dir[500];

	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, "PWD", 3) == EXIT_SUCCESS)
		{
			free(p->aux->content);
			p->aux->content = ft_strjoin("=", getcwd(dir, 500));
			if (!p->aux->content)
				return ;
			break ;
		}
		p->aux = p->aux->next_env;
	}
}

void	change_oldpwd(t_paco *p)
{
	char	dir[500];

	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, "OLDPWD", 6) == EXIT_SUCCESS)
		{
			free(p->aux->content);
			p->aux->content = ft_strjoin("=", getcwd(dir, 500));
			if (!p->aux->content)
				return ;
			break ;
		}
		p->aux = p->aux->next_env;
	}
}

void	change_oldpwd2(t_paco *p, char *dir)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, "OLDPWD", 6) == 0)
		{
			free(p->aux->content);
			p->aux->content = ft_strjoin("=", dir);
			if (!p->aux->content)
				return ;
			break ;
		}
		p->aux = p->aux->next_env;
	}
}

void	change_cd(t_paco *p, int option)
{
	if (option == 0)
	{
		get_cd_path(p, "HOME");
		chdir(p->tmp);
		change_pwd(p);
	}
}