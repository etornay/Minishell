/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:19:31 by etornay-          #+#    #+#             */
/*   Updated: 2024/02/09 13:58:05 by etornay-         ###   ########.fr       */
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

void	exec_pwd(t_paco *p)
{
	char	dir[500];

	p->act_dir = getcwd(dir, 500);
	if (p->act_dir == NULL)
		return ;
	ft_printf("%s\n", p->act_dir);
}

void	exec_cd(t_paco *p, char **s)
{
	char	dir[500];
	int		flag;

	if (!ft_strncmp(s[0], "cd\0", 3) && s[1] == NULL)
		change_cd(p, 0);
	else if (!ft_strncmp(s[0], "cd\0", 3) && s[1])
	{
		getcwd(dir, 500);
		flag = chdir(s[1]);
		if (flag == 0)
			change_pwd(p);
		else if (flag == -1)
		{
			p->tmp = ft_strjoin("bash: cd: ", s[1]);
			if (!p->tmp)
				return ;
			p->cd_error = ft_strjoin(p->tmp, ": No such file or directory");
			if (!p->cd_error)
				return ;
			ft_putendl_fd(p->cd_error, 2);
		}
	}
}
