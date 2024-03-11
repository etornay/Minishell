/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:19:31 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/11 12:11:53 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_unset(t_paco *p, char *name)
{
	t_env	*del;
	t_env	*prev;

	if (!name)
		return ;
	p->aux = p->l_env;
	prev = NULL;
	while (p->aux != NULL)
	{
		if (!ft_strncmp(p->aux->name, name, ft_strlen(name)))
		{
			del = p->aux;
			if (prev)
				prev->next_env = p->aux->next_env;
			else
				p->l_env = p->aux->next_env;
			free(del->name);
			if (del->content != NULL)
				free(del->content);
			free(del);
			break ;
		}
		prev = p->aux;
		p->aux = p->aux->next_env;
	}
}

void	exec_pwd(t_paco *p)
{
	char	dir[500];

	p->act_dir = getcwd(dir, 500);
	if (p->act_dir == NULL)
		return ;
	ft_printf("%s\n", p->act_dir);
}

void	exec_cd(t_paco *p, char **s, int flag)
{
	char	dir[500];

	if (ft_strncmp(s[0], "cd\0", 3) == EXIT_SUCCESS && s[1] == NULL)
		change_cd(p);
	else if (!ft_strncmp(s[0], "cd\0", 3) && s[1])
	{
		getcwd(dir, 500);
		flag = chdir(s[1]);
		if (flag == 0)
		{
			change_oldpwd2(p, dir);
			change_pwd(p);
		}
		else if (flag == -1)
		{
			p->tmp = ft_strjoin("bash: cd: ", s[1]);
			if (!p->tmp)
				return ;
			p->cd_error = ft_strjoin(p->tmp, ": No such file or directory");
			if (!p->cd_error)
				return ;
			ft_putendl_fd(p->cd_error, 2);
			free_cd_error(p);
		}
	}
}
